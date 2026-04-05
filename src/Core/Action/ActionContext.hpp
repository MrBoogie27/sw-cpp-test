#pragma once

#include "Core/World/Map.hpp"

#include <IO/System/EventLog.hpp>

namespace sw::core
{
	class UnitRegistry;

	struct ActionContext
	{
		EventLog& logger;
		Map& map;
		UnitRegistry& units;

		const uint32_t currentTurn;
	};
}
