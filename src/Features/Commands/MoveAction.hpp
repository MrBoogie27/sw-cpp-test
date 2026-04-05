#pragma once

#include <Core/Action/IAction.hpp>
#include <Core/Units/IUnit.hpp>
#include <optional>

namespace sw::features
{
	class MoveAction : public core::IAction
	{
	public:
		bool canAddFor(core::IUnit& unit) override;
		bool execute(core::IUnit& unit, core::ActionContext& actionCtx) override;
	};
}
