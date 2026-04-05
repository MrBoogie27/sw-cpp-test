#pragma once

#include "Core/World/Point.hpp"
#include "UnitState.hpp"

#include <IO/System/TypeRegistry.hpp>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>

namespace sw::core
{
	using UnitId = uint32_t;

	class ActionContext;

	class IUnit
	{
	public:
		virtual UnitId getId() const = 0;
		virtual const std::string& getUnitType() const = 0;
		virtual UnitState getState() const = 0;
		virtual const TypeRegistry& getCharacteristics() const = 0;

		virtual void setState(UnitState s) = 0;
		virtual void setMoveOrder(std::optional<Point> targetPoint) = 0;
		virtual std::optional<Point> getMoveOrderTarget() const = 0;
		virtual bool makeAction(ActionContext& actionCtx) = 0;

		virtual ~IUnit() = default;
	};

	using IUnitPtr = std::shared_ptr<IUnit>;
}
