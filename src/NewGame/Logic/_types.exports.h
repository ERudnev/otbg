#pragma once

#include "NewGame/Logic/Entities/Map.h"
#include "NewGame/Logic/Entities/Unit.h"
#include "NewGame/Logic/Abilities/Rending.h"
#include "NewGame/Logic/Abilities/MeleeAttack.h"
#include "NewGame/Logic/Abilities/RangedAttack.h"
#include "NewGame/Logic/Effects/Poisoned.h"
#include "NewGame/Core/Types.h"

// See docs about this type exported out of World
namespace swexp::game
{

}



// TODO: separate as project growth
// currently it is "root types garbage for Game Logic"
namespace swexp::game::types
{
	using UnitId = entity::Unit::Id;

	using Position = entity::Map::Position;
	using HitPoints = entity::Unit::HitPoints;
	using Strength = ability::MeleeAttack::Strength;
	using Range = ability::RangedAttack::Range;
	using Chance = ability::Rending::Chance;
	using Rending = ability::Rending::Damage;
}
