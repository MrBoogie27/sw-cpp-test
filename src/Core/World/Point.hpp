#pragma once

#include <cstdint>
#include <tuple>

namespace sw::core
{
	struct Point
	{
		uint32_t x;
		uint32_t y;

		bool operator==(const Point& other) const
		{
			return std::tie(x, y) == std::tie(other.x, other.y);
		}
	};
}
