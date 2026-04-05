#pragma once

#include "Core/Units/IUnit.hpp"
#include "Point.hpp"

#include <cstdint>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace sw::core
{
	class Map
	{
	private:
		const uint32_t _height;
		const uint32_t _width;

		using Cell = std::unordered_set<UnitId>;
		using Row = std::unordered_map<uint32_t, Cell>;
		std::unordered_map<uint32_t, Row> _maps;
		std::unordered_map<uint32_t, Point> _unitPositions;

	public:
		explicit Map(uint32_t height, uint32_t width);

		void addUnitWithPosition(UnitId id, Point point);
		bool updateUnitPosition(UnitId id, Point nextPoint);
		bool deleteUnit(UnitId id);

		std::optional<Point> getUnitPosition(UnitId id) const;
		std::vector<UnitId> getUnits(Point point) const;
		Point getSize() const;
	};

}
