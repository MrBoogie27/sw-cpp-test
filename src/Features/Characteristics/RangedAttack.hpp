#pragma once

#include <cstdint>

namespace sw::features
{

	struct RangedAttack
	{
		explicit RangedAttack(uint32_t agility, uint32_t range) :
				agility(agility),
				range(range)
		{}

		uint32_t agility;
		uint32_t range;
	};

}
