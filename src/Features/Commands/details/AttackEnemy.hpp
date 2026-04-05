#pragma once

#include <Core/Action/ActionContext.hpp>
#include <Core/Units/IUnit.hpp>
#include <cstdint>
#include <vector>

namespace sw::features::details
{
	void attackUnit(
		core::IUnit& attackerUnit, core::IUnit& targetUnit, const core::ActionContext& actionCtx, uint32_t damage);

}
