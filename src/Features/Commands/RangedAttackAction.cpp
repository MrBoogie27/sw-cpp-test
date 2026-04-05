#include "RangedAttackAction.hpp"

#include "Features/Characteristics/Health.hpp"
#include "Features/Characteristics/RangedAttack.hpp"
#include "Features/Commands/details/AttackEnemy.hpp"
#include "Features/Commands/details/FindClosestTarget.hpp"

namespace sw::features
{
	bool RangedAttackAction::canAddFor(core::IUnit& unit)
	{
		return static_cast<bool>(unit.getCharacteristics().get<RangedAttack>());
	}

	bool RangedAttackAction::execute(core::IUnit& unit, core::ActionContext& actionCtx)
	{
		auto rangedAttack = unit.getCharacteristics().get<RangedAttack>();
		if (!rangedAttack)
		{
			throw std::logic_error("Cannot find rangedAttack characteristic");
		}

		auto enemy = details::findClosestTarget(unit, actionCtx, 2, rangedAttack->range);

		if (!enemy)
		{
			return false;
		}

		details::attackUnit(unit, *enemy, actionCtx, rangedAttack->agility);
		return true;
	}
}
