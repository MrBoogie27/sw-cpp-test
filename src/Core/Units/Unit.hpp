#pragma once

#include "Core/Action/IAction.hpp"
#include "IUnit.hpp"

#include <memory>
#include <string>
#include <vector>

namespace sw::core
{
	class Unit : public IUnit
	{
	private:
		UnitId _id;
		std::string _type;
		UnitState _state;
		std::optional<core::Point> _targetPoint;
		std::vector<std::unique_ptr<IAction>> _availableActions;
		TypeRegistry _characteristics;

	public:
		explicit Unit(UnitId id, std::string type, UnitState state = UnitState::Alive);

		uint32_t getId() const override;
		const std::string& getUnitType() const override;
		UnitState getState() const override;
		void setState(UnitState s) override;
		void setMoveOrder(std::optional<Point> targetPoint) override;
		std::optional<Point> getMoveOrderTarget() const override;

		bool makeAction(ActionContext& actionCtx) override;

		const TypeRegistry& getCharacteristics() const override;

		void addAction(std::unique_ptr<IAction> action);

		template <typename T, typename... Args>
		void addCharacteristic(Args&&... args)
		{
			std::ignore = _characteristics.emplace<T>(std::forward<Args>(args)...);
		}
	};
}
