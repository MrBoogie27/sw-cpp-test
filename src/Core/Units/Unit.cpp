#include "Unit.hpp"

#include <stdexcept>

namespace sw::core
{
	Unit::Unit(UnitId id, std::string type, UnitState state) :
			_id(id),
			_type(type),
			_state(state)
	{}

	uint32_t Unit::getId() const
	{
		return _id;
	}

	const std::string& Unit::getUnitType() const
	{
		return _type;
	}

	UnitState Unit::getState() const
	{
		return _state;
	}

	void Unit::setState(UnitState s)
	{
		_state = s;
	}

	void Unit::setMoveOrder(std::optional<Point> targetPoint)
	{
		_targetPoint = targetPoint;
	}

	std::optional<Point> Unit::getMoveOrderTarget() const
	{
		return _targetPoint;
	}

	bool Unit::makeAction(ActionContext& actionCtx)
	{
		for (auto it = _availableActions.begin(); it != _availableActions.end(); it++)
		{
			auto& action = *it;
			if (action->execute(*this, actionCtx))
			{
				return true;
			}
		}
		return false;
	}

	const TypeRegistry& Unit::getCharacteristics() const
	{
		return _characteristics;
	}

	void Unit::addAction(std::unique_ptr<IAction> action)
	{
		if (!action->canAddFor(*this))
		{
			throw std::logic_error("Can't add action");
		}
		_availableActions.emplace_back(std::move(action));
	}

}
