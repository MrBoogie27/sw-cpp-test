#pragma once

#include "ActionContext.hpp"
#include "Core/Units/IUnit.hpp"

#include <IO/System/EventLog.hpp>

namespace sw::core
{
	class IAction
	{
	public:
		virtual bool canAddFor(IUnit& unit) = 0;
		virtual bool execute(IUnit& unit, ActionContext& actionCtx) = 0;
		virtual ~IAction() = default;
	};

}
