#pragma once

#include "Core/World/Point.hpp"

#include <cmath>
#include <cstdint>
#include <vector>

namespace
{
	inline uint32_t distance(uint32_t fst, uint32_t snd)
	{
		return (fst > snd) ? (fst - snd) : (snd - fst);
	}
}

namespace sw::core::utils
{

	inline uint32_t manhattan(Point a, Point b)
	{
		uint32_t dx = distance(a.x, b.x);
		uint32_t dy = distance(a.y, b.y);
		return dx + dy;
	}

	inline uint32_t chebyshev(Point a, Point b)
	{
		uint32_t dx = distance(a.x, b.x);
		uint32_t dy = distance(a.y, b.y);
		return std::max(dx, dy);
	}

	inline uint64_t euclideanSq(Point a, Point b)
	{
		uint32_t dx = distance(a.x, b.x);
		uint32_t dy = distance(a.y, b.y);
		return dx * dx + dy * dy;
	}

}
