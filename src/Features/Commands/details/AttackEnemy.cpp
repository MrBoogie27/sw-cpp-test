#include "Features/Characteristics/Health.hpp"
#include "FindClosestTarget.hpp"

#include <Core/Units/IUnit.hpp>
#include <Core/Units/UnitState.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>

namespace sw::features::details
{
	void attackUnit(
		core::IUnit& attackerUnit, core::IUnit& targetUnit, const core::ActionContext& actionCtx, uint32_t damage)
	{
		auto targetHealth = targetUnit.getCharacteristics().get<Health>();
		if (!targetHealth)
		{
			throw std::runtime_error("Target unit without health");
		}

		uint32_t realDamage = std::min(targetHealth->hp, damage);
		targetHealth->hp -= realDamage;
		actionCtx.logger.log(
			actionCtx.currentTurn,
			io::UnitAttacked{attackerUnit.getId(), targetUnit.getId(), realDamage, targetHealth->hp});
		if (targetHealth->hp == 0)
		{
			targetUnit.setState(core::UnitState::Dead);
			actionCtx.logger.log(actionCtx.currentTurn, io::UnitDied{targetUnit.getId()});
		}
	}

}
