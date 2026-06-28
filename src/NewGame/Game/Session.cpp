#include "Session.h"

#include "Core/Model/Intertype.h"
#include "IO/interface.include.h"
#include "NewGame/Core/Interface/macros.h"

// TODO: moe to dedicated "my schema" file...
// To build Schema
#include "NewGame/Logic/Abilities/LandMovement.h"
#include "NewGame/Logic/Abilities/MeleeAttack.h"
#include "NewGame/Logic/Abilities/PoisonArrows.h"
#include "NewGame/Logic/Abilities/RangedAttack.h"
#include "NewGame/Logic/Abilities/Rending.h"
#include "NewGame/Logic/Compositions/Hunter.h"
#include "NewGame/Logic/Compositions/Swordsman.h"
#include "NewGame/Logic/Effects/OrderedToMove.h"
#include "NewGame/Logic/Effects/Poisoned.h"
#include "NewGame/Logic/Effects/Rended.h"
#include "NewGame/Logic/Entities/Map.h"
#include "NewGame/Logic/Entities/Unit.h"
#include "NewGame/Logic/Entities/World.h"

namespace swexp::game
{

	// priate Schema init:
	using namespace swexp::core::api;

	inline Schema createSchema() {
		return core::model::intertype::SchemaData::build<
			entity::World,
			entity::Map,
			entity::Unit,
			ability::LandMovement,
			ability::MeleeAttack,
			ability::RangedAttack,
			ability::Rending,
			ability::PoisonArrows,
			composition::Swordsman,
			composition::Hunter,
			effect::Poisoned,
			effect::OrderedToMove,
			effect::Rended
		>();
	}


	Session::Session(sw::EventSystem& events)
		: eventReceiver(events)
		, schema(createSchema())
		, state(schema)
		, world(-1) // fill below
	{
		_INCOMPLETE_;
	}

	void Session::createMap(uint32_t, uint32_t)
	{
		_INCOMPLETE_;
	}

	void Session::spawnUnit(uint32_t, Position, uint32_t, uint32_t, uint32_t, uint32_t)
	{
		_INCOMPLETE_;
	}

	void Session::march(uint32_t, Position)
	{
		_INCOMPLETE_;
	}

	bool Session::isGameOver() const
	{
		_INCOMPLETE_;
		return true;
	}

	void Session::step()
	{
		_INCOMPLETE_;
	}
}
