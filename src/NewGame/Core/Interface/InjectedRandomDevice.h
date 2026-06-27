#pragma once

#include <cstdint>

namespace swexp::core::interface
{
	struct InjectedRandomDevice
	{
		static void init();
		static void init(uint32_t seed);
		static uint32_t next();
	};
}
