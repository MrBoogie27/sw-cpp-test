#include "GameSimulation.hpp"

#include "Core/Units/IUnit.hpp"
#include "Core/Units/UnitState.hpp"
#include "IO/Events/MarchStarted.hpp"

#include <IO/Events/MapCreated.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <stdexcept>

namespace sw::core
{
	GameSimulation::GameSimulation(EventLog& logger) :
			_logger(logger)
	{}

	void GameSimulation::createMap(uint32_t width, uint32_t height)
	{
		if (_map)
		{
			throw std::runtime_error("GameSimulation already has map");
		}
		_map = std::make_unique<Map>(height, width);

		_logger.log(_currentTurn, io::MapCreated{width, height});
	}

	void GameSimulation::addUnit(UnitId unitId, IUnitPtr unit, Point point)
	{
		if (!_map)
		{
			throw std::runtime_error("GameSimulation has not map");
		}

		if (!_aliveUnits.addUnit(unitId, unit))
		{
			throw std::invalid_argument("Unit with ID = " + std::to_string(unitId) + " already exists");
		}

		_map->addUnitWithPosition(unitId, point);
		_logger.log(_currentTurn, io::UnitSpawned{unitId, unit->getUnitType(), point.x, point.y});
	}

	void GameSimulation::issueMarch(UnitId unitId, Point targetPoint)
	{
		if (!_map)
		{
			throw std::runtime_error("GameSimulation has not map");
		}
		Point mapSize = _map->getSize();
		if (targetPoint.x >= mapSize.x || targetPoint.y >= mapSize.y)
		{
			throw std::invalid_argument("target point is not in the map");
		}
		std::optional<core::Point> currentPoint = _map->getUnitPosition(unitId);
		if (!currentPoint)
		{
			throw std::runtime_error("Unit " + std::to_string(unitId) + " not found on map");
		}
		if (*currentPoint == targetPoint)
		{
			return;
		}

		core::IUnitPtr unit = _aliveUnits.getUnit(unitId);
		if (!unit)
		{
			throw std::runtime_error("not found alive unit");
		}

		unit->setMoveOrder(targetPoint);
		_logger.log(
			_currentTurn, io::MarchStarted{unitId, currentPoint->x, currentPoint->y, targetPoint.x, targetPoint.y});
	}

	void GameSimulation::initialize()
	{
		if (!_map)
		{
			throw std::runtime_error("GameSimulation has not map");
		}
		_currentTurn++;
	}

	void GameSimulation::execute()
	{
		while (executeTurn())
		{
		}
	}

	bool GameSimulation::executeTurn()
	{
		if (!_map)
		{
			throw std::runtime_error("GameSimulation not initialized");
		}

		if (_aliveUnits.size() <= 1)
		{
			return false;
		}

		uint32_t countActions{0};

		ActionContext actionCtx = getActionContext();

		for (IUnitPtr unit : _aliveUnits)
		{
			if (unit->makeAction(actionCtx))
			{
				countActions++;
			}
		}

		if (countActions == 0)
		{
			return false;
		}

		clearDeadUnits();
		_currentTurn++;

		return true;
	}

	ActionContext GameSimulation::getActionContext()
	{
		return ActionContext{_logger, *_map, _aliveUnits, _currentTurn};
	}

	uint32_t GameSimulation::getCurrentTurn() const
	{
		return _currentTurn;
	}

	void GameSimulation::clearDeadUnits()
	{
		std::vector<UnitId> deadUnitIds;
		for (const auto unit : _aliveUnits)
		{
			if (unit->getState() == UnitState::Dead)
			{
				deadUnitIds.push_back(unit->getId());
			}
		}

		for (UnitId unitId : deadUnitIds)
		{
			std::ignore = _aliveUnits.deleteUnit(unitId);
			if (!_map->deleteUnit(unitId))
			{
				throw std::runtime_error("cannot delete unitId = " + std::to_string(unitId) + " from map");
			}
		}
	}

}
