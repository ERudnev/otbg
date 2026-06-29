#include "World.h"

#include "Core/Model/Intertype.h"
#include "Core/Mechanism/StateProcessing.h"
#include "IO/interface.include.h"
#include "NewGame/Core/Interface/macros.h"
#include "NewGame/Game/World.h"

// TODO: moe to dedicated "my schema" file...
// To build Schema
#include "NewGame/Game/Abilities/LandMovement.h"
#include "NewGame/Game/Abilities/MeleeAttack.h"
#include "NewGame/Game/Abilities/PoisonArrows.h"
#include "NewGame/Game/Abilities/RangedAttack.h"
#include "NewGame/Game/Abilities/Rending.h"
#include "NewGame/Game/Compositions/Hunter.h"
#include "NewGame/Game/Compositions/Swordsman.h"
#include "NewGame/Game/Effects/OrderedToMove.h"
#include "NewGame/Game/Effects/Poisoned.h"
#include "NewGame/Game/Effects/Rended.h"
#include "NewGame/Game/Entities/Map.h"
#include "NewGame/Game/Entities/Unit.h"
#include <memory>


namespace swexp::game
{

	// priate Schema init:
	using namespace swexp::core::api;

	inline Schema createSchema() {
		return core::model::intertype::SchemaData::build<
			// TODO: add Singletons to State as values: entity::World,
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


	World::World(sw::EventSystem& events)
		: eventReceiver(events)
		, schema(createSchema())
		, state(schema)
	{
		currentTurn = 0;
		map = state.line<entity::Map>().createEntity({0,0});
	}

	void World::normalize()
	{
		//const auto results = core::operations::Normalizer::repair(state);
	}

	void World::createMap(uint32_t, uint32_t)
	{
		_INCOMPLETE_;
	}

	void World::spawnSwordsman(UnitId id, const composition::Swordsman::Actions::SpawnParameters& parameters)
	{
		Transaction tx(state, eventReceiver);
		// check if caller wants to replace unit
		//with<entity::Unit>::remove(state, id);
		//core::operations::normalize(state);
		registeredUnits[id] = with<composition::Swordsman>::spawn(tx, parameters);

		_INCOMPLETE_;
	}

	void World::march(uint32_t, Position)
	{
		_INCOMPLETE_;
	}

	bool World::isGameOver() const
	{
		_INCOMPLETE_;
		return true;
	}

	void World::step()
	{
		_INCOMPLETE_;
	}
}
