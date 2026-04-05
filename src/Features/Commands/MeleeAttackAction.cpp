#include "MeleeAttackAction.hpp"

#include "Features/Characteristics/Health.hpp"
#include "Features/Characteristics/MeleeAttack.hpp"
#include "Features/Commands/details/AttackEnemy.hpp"
#include "Features/Commands/details/FindClosestTarget.hpp"

#include <memory>
#include <stdexcept>

namespace sw::features
{
	bool MeleeAttackAction::canAddFor(core::IUnit& unit)
	{
		return static_cast<bool>(unit.getCharacteristics().get<MeleeAttack>());
	}

	bool MeleeAttackAction::execute(core::IUnit& unit, core::ActionContext& actionCtx)
	{
		auto meleeAttack = unit.getCharacteristics().get<MeleeAttack>();
		if (!meleeAttack)
		{
			throw std::logic_error("Cannot find meleeAttack characteristic");
		}

		auto enemy = details::findClosestTarget(unit, actionCtx, 1, 1);

		if (!enemy)
		{
			return false;
		}

		details::attackUnit(unit, *enemy, actionCtx, meleeAttack->strength);
		return true;
	}

}
