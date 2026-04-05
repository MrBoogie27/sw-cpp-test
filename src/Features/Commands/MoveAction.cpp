#include "MoveAction.hpp"

#include "Features/Characteristics/Mobility.hpp"

#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <optional>
#include <stdexcept>

namespace
{
	void validateMovement(const sw::core::Map& map, const sw::core::Point& targetPoint)
	{
		sw::core::Point mapSize = map.getSize();
		if (targetPoint.x >= mapSize.x || targetPoint.y >= mapSize.y)
		{
			throw std::logic_error("targetPoint more than map");
		}
	}

	bool checkCanMove(const sw::core::Map& map, const sw::core::Point& targetPoint)
	{
		auto units = map.getUnits(targetPoint);
		return units.empty();
	}

	bool tryMoveInDirection(sw::core::Map& map, sw::core::UnitId unitId, const sw::core::Point& nextPoint)
	{
		if (!checkCanMove(map, nextPoint))
		{
			return false;
		}

		if (!map.updateUnitPosition(unitId, nextPoint))
		{
			throw std::runtime_error("Cannot occupy an empty cell");
		}

		return true;
	}

	bool tryMoveStep(sw::core::Map& map, sw::core::UnitId unitId, const sw::core::Point& targetPoint)
	{
		sw::core::Point currentPoint = *map.getUnitPosition(unitId);

		if (currentPoint == targetPoint)
		{
			return false;
		}

		if (currentPoint.x != targetPoint.x)
		{
			int32_t delta = (currentPoint.x > targetPoint.x ? -1 : 1);
			sw::core::Point nextPoint{currentPoint.x + delta, currentPoint.y};
			if (tryMoveInDirection(map, unitId, nextPoint))
			{
				return true;
			}
		}

		if (currentPoint.y != targetPoint.y)
		{
			int32_t delta = (currentPoint.y > targetPoint.y ? -1 : 1);
			sw::core::Point nextPoint{currentPoint.x, currentPoint.y + delta};
			return tryMoveInDirection(map, unitId, nextPoint);
		}
		return false;
	}
}

namespace sw::features
{
	bool MoveAction::canAddFor(core::IUnit& unit)
	{
		return static_cast<bool>(unit.getCharacteristics().get<Mobility>());
	}

	bool MoveAction::execute(core::IUnit& unit, core::ActionContext& actionCtx)
	{
		std::optional<core::Point> targetPoint = unit.getMoveOrderTarget();
		if (!targetPoint)
		{
			return false;
		}

		auto mobility = unit.getCharacteristics().get<Mobility>();
		if (!mobility)
		{
			throw std::logic_error("Cannot find speed characteristic");
		}

		if (mobility->speed == 0)
		{
			return false;
		}

		validateMovement(actionCtx.map, *targetPoint);

		uint32_t unitId = unit.getId();

		if (!tryMoveStep(actionCtx.map, unitId, *targetPoint))
		{
			return false;
		}

		for (size_t step = 1; step < mobility->speed; step++)
		{
			if (!tryMoveStep(actionCtx.map, unitId, *targetPoint))
			{
				break;
			}
		}

		core::Point finalPosition = *actionCtx.map.getUnitPosition(unitId);
		actionCtx.logger.log(actionCtx.currentTurn, sw::io::UnitMoved{unitId, finalPosition.x, finalPosition.y});

		if (finalPosition == *targetPoint)
		{
			unit.setMoveOrder(std::nullopt);
			actionCtx.logger.log(actionCtx.currentTurn, sw::io::MarchEnded{unitId, finalPosition.x, finalPosition.y});
		}

		return true;
	}
}
