#pragma once

#include "IUnit.hpp"

#include <cstdint>
#include <list>
#include <unordered_map>
#include <vector>

namespace sw::core
{
	class UnitRegistry
	{
	private:
		std::list<IUnitPtr> _addedOrder;
		using ListUnitIterator = decltype(_addedOrder)::iterator;
		using ListUnitConstIterator = decltype(_addedOrder)::const_iterator;
		std::unordered_map<UnitId, ListUnitIterator> _units;

	public:
		bool addUnit(UnitId unitId, IUnitPtr unit);
		bool deleteUnit(UnitId unitId);

		IUnitPtr getUnit(UnitId unitId) const;
		std::vector<UnitId> getAllUnits() const;

		ListUnitConstIterator begin() const;
		ListUnitConstIterator end() const;
		size_t size() const;
	};

}
