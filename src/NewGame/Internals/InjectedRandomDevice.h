#pragma once

#include <cstdint>

namespace sw::game
{
	class InjectedRandomDevice
	{
	public:
		static void init();
		static void init(uint32_t seed);
		static uint32_t next();
	};
}
