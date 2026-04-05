#pragma once

#include "Core/Units/IUnit.hpp"
#include "Core/Units/Unit.hpp"
#include "Core/Units/UnitRegistry.hpp"
#include "Core/World/Map.hpp"

#include <IO/System/EventLog.hpp>
#include <cstdint>
#include <memory>

namespace sw::core
{
	class GameSimulation
	{
	private:
		EventLog& _logger;
		uint32_t _currentTurn{1};
		std::unique_ptr<Map> _map;

		UnitRegistry _aliveUnits;
		UnitRegistry _deadUnits;

	public:
		explicit GameSimulation(EventLog& logger);
		~GameSimulation() = default;

		GameSimulation(const GameSimulation&) = delete;
		GameSimulation& operator=(const GameSimulation&) = delete;

		void createMap(uint32_t width, uint32_t height);
		void addUnit(UnitId unitId, IUnitPtr unit, Point point);
		void issueMarch(UnitId unitId, Point targetPoint);
		void initialize();

		void execute();
		bool executeTurn();

		ActionContext getActionContext();
		uint32_t getCurrentTurn() const;

	private:
		void clearDeadUnits();
	};

}
