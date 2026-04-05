#include "FindClosestTarget.hpp"

#include "Features/Characteristics/Health.hpp"

#include <Core/Units/IUnit.hpp>
#include <Core/Units/UnitRegistry.hpp>
#include <Core/Utils/Distance.hpp>

namespace sw::features::details
{
	core::IUnitPtr findClosestTarget(
		const core::IUnit& unit, const core::ActionContext& actionCtx, uint32_t minDist, uint32_t maxDist)
	{
		core::UnitId unitId = unit.getId();
		core::Point currentPoint = *actionCtx.map.getUnitPosition(unitId);

		core::IUnitPtr targetUnit;
		uint64_t minDistSq = static_cast<uint64_t>(minDist) * minDist;
		uint64_t maxDistSq = static_cast<uint64_t>(maxDist) * maxDist;
		uint32_t targetDistSq = maxDistSq + 1;

		for (const core::IUnitPtr enemyUnit : actionCtx.units)
		{
			core::UnitId enemyId = enemyUnit->getId();
			if (enemyId == unitId)
			{
				continue;
			}

			auto health = enemyUnit->getCharacteristics().get<Health>();
			if (!health || health->hp == 0)
			{
				continue;
			}

			std::optional<core::Point> enemyPoint = actionCtx.map.getUnitPosition(enemyId);
			if (!enemyPoint)
			{
				continue;
			}

			uint64_t distSq = core::utils::euclideanSq(currentPoint, *enemyPoint);
			if (minDistSq >= minDist && distSq <= maxDistSq && distSq < targetDistSq)
			{
				targetDistSq = distSq;
				targetUnit = enemyUnit;
			}
		}

		return targetUnit;
	}

}
