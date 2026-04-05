#pragma once

#include <cstdint>

namespace sw::features
{

	struct MeleeAttack
	{
		explicit MeleeAttack(uint32_t strength) :
				strength(strength)
		{}

		uint32_t strength;
	};

}
