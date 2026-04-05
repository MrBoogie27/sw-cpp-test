#pragma once

#include <Core/Action/ActionContext.hpp>
#include <Core/Units/IUnit.hpp>
#include <cstdint>

namespace sw::features::details
{
	core::IUnitPtr findClosestTarget(
		const core::IUnit& unit, const core::ActionContext& actionCtx, uint32_t minDist, uint32_t maxDist);

}
