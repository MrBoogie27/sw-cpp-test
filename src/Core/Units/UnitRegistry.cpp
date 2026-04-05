#include "UnitRegistry.hpp"

namespace sw::core
{
	bool UnitRegistry::addUnit(UnitId unitId, IUnitPtr unit)
	{
		if (_units.contains(unitId))
		{
			return false;
		}
		ListUnitIterator listIt = _addedOrder.insert(_addedOrder.end(), unit);
		_units[unitId] = listIt;
		return true;
	}

	bool UnitRegistry::deleteUnit(UnitId unitId)
	{
		auto mapIt = _units.find(unitId);
		if (mapIt == _units.end())
		{
			return false;
		}
		ListUnitIterator listIt = mapIt->second;
		_addedOrder.erase(listIt);
		_units.erase(mapIt);
		return true;
	}

	IUnitPtr UnitRegistry::getUnit(UnitId unitId) const
	{
		auto mapIt = _units.find(unitId);
		if (mapIt == _units.end())
		{
			return IUnitPtr();
		}
		ListUnitIterator listIt = mapIt->second;
		return *listIt;
	}

	std::vector<UnitId> UnitRegistry::getAllUnits() const
	{
		std::vector<UnitId> unitIds;
		unitIds.reserve(_addedOrder.size());
		for (auto it = _addedOrder.begin(); it != _addedOrder.end(); it++)
		{
			unitIds.push_back((*it)->getId());
		}
		return unitIds;
	}

	UnitRegistry::ListUnitConstIterator UnitRegistry::begin() const
	{
		return _addedOrder.begin();
	}

	UnitRegistry::ListUnitConstIterator UnitRegistry::end() const
	{
		return _addedOrder.end();
	}

	size_t UnitRegistry::size() const
	{
		return _addedOrder.size();
	}
}
