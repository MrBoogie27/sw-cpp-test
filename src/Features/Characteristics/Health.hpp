#pragma once

#include <cstdint>

namespace sw::features
{

	struct Health
	{
		explicit Health(uint32_t hp) :
				hp(hp)
		{}

		uint32_t hp;
	};

}
