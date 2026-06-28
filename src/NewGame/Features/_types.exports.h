#pragma once

#include "NewGame/Features/Map.h"
#include "NewGame/Features/Body.h"
#include "NewGame/Features/MeleeAttack.h"
#include "NewGame/Features/RangedAttack.h"
#include "NewGame/Features/RendingAbility.h"
#include "NewGame/Features/PoisonEffect.h"
#include "NewGame/Core/Types.h"

// TODO: separate as project growth
// currently it is "root types garbage for Game Logic"
namespace swexp::game::types
{
	using UnitId = core::types::Id;

	using Position = entity::Map::Position;
	using HitPoints = entity::Body::HitPoints;
	using Strength = entity::MeleeAttack::Strength;
	using Range = entity::RangedAttack::Range;
	using Chance = entity::RendingAbility::Chance;
	using Rending = entity::RendingAbility::Rending;
	using Poison = entity::PoisonEffect::Poison;
}
