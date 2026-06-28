#pragma once

#include "NewGame/Game/Entities/Map.h"
#include "NewGame/Game/Entities/Unit.h"
#include "NewGame/Game/Abilities/Rending.h"
#include "NewGame/Game/Abilities/MeleeAttack.h"
#include "NewGame/Game/Abilities/RangedAttack.h"
#include "NewGame/Game/Effects/Poisoned.h"
#include "NewGame/Core/Types.h"

// TODO: separate as project growth
// currently it is "root types garbage for Game Logic"

//NB: this is "old interface names" and to be removed
namespace swexp::game::api
{
	// this is public UnitId, used in API
	using UnitId = uint32_t;

	// Position is safe now, can be uses 1x1 in the public API
	using Position = entity::Map::Position;

	/*
	using Position = entity::Map::Position;
	using HitPoints = entity::Unit::HitPoints;
	using Strength = ability::MeleeAttack::Strength;
	using Range = ability::RangedAttack::Range;
	using Chance = ability::Rending::Chance;
	using Rending = ability::Rending::Amount;*/
}
