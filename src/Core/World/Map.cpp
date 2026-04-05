#include "Map.hpp"

#include <stdexcept>

namespace sw::core
{

	Map::Map(uint32_t height, uint32_t width) :
			_height(height),
			_width(width)
	{}

	void Map::addUnitWithPosition(UnitId id, Point point)
	{
		if (point.x >= _width || point.y >= _height)
		{
			throw std::invalid_argument("bad x, y");
		}
		if (_unitPositions.contains(id))
		{
			throw std::logic_error("unit already exist");
		}

		_unitPositions[id] = point;
		std::unordered_set<UnitId>& units = _maps[point.x][point.y];
		units.insert(id);
	}

	bool Map::updateUnitPosition(UnitId id, Point nextPoint)
	{
		auto it = _unitPositions.find(id);
		if (it == _unitPositions.end())
		{
			return false;
		}
		if (nextPoint.x >= _width || nextPoint.y >= _height)
		{
			return false;
		}

		Point& currentPoint = it->second;
		_maps[currentPoint.x][currentPoint.y].erase(id);
		_maps[nextPoint.x][nextPoint.y].insert(id);
		currentPoint = nextPoint;
		return true;
	}

	bool Map::deleteUnit(UnitId id)
	{
		auto pointIt = _unitPositions.find(id);
		if (pointIt == _unitPositions.end())
		{
			return false;
		}
		auto& point = pointIt->second;

		auto rowIt = _maps.find(point.x);
		if (rowIt == _maps.end())
		{
			return false;
		}
		Row& row = rowIt->second;
		auto cellIt = row.find(point.y);
		if (cellIt == row.end())
		{
			return false;
		}
		std::unordered_set<UnitId>& ids = cellIt->second;
		ids.erase(id);
		if (ids.empty())
		{
			row.erase(cellIt);
		}
		if (row.empty())
		{
			_maps.erase(rowIt);
		}

		_unitPositions.erase(id);

		return true;
	}

	std::optional<Point> Map::getUnitPosition(UnitId id) const
	{
		auto it = _unitPositions.find(id);
		if (it == _unitPositions.end())
		{
			return std::nullopt;
		}
		return it->second;
	}

	std::vector<UnitId> Map::getUnits(Point point) const
	{
		auto rowIt = _maps.find(point.x);
		if (rowIt == _maps.end())
		{
			return std::vector<UnitId>();
		}
		const Row& row = rowIt->second;
		auto cellIt = row.find(point.y);
		if (cellIt == row.end())
		{
			return std::vector<UnitId>();
		}
		const std::unordered_set<UnitId>& ids = cellIt->second;
		return std::vector<UnitId>(ids.begin(), ids.end());
	}

	Point Map::getSize() const
	{
		return Point{_width, _height};
	}

}
