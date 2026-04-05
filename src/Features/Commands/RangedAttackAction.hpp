#pragma once

#include <Core/Action/IAction.hpp>
#include <Core/Units/IUnit.hpp>

namespace sw::features
{
	class RangedAttackAction : public core::IAction
	{
		bool canAddFor(core::IUnit& unit) override;
		bool execute(core::IUnit& unit, core::ActionContext& actionCtx) override;
	};

}
