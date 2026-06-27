#pragma once

#include "NewGame/Core/Types.h"
#include <cstdint>

// TODO: separate as project growth
// currently it is "root types garbage for Game Logic"
namespace swexp::game::types
{
	using UnitId = core::types::Id;

	// TODO: make signed
	// TODO: make closer to "Game Space" once it appears...
	struct Position
	{
		uint32_t x{0};
		uint32_t y{0};
	};

	// Will be "Unit" props
	using HitPoints = uint32_t;

	// Will be "melee functionality" props
	using Strength = uint32_t;
	using Chance = uint32_t;
	using Rending = uint32_t;
}
