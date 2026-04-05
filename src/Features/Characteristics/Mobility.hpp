#pragma once

#include <cstdint>
#include <optional>

namespace sw::features
{
	struct Mobility
	{
		explicit Mobility(uint32_t speed) :
				speed(speed)
		{}

		uint32_t speed;
	};

}
