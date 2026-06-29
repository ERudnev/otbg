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
#include <algorithm>
#include <memory>
#include <stdexcept>


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

	void World::createMap(uint32_t width, uint32_t height)
	{
		Transaction tx(state, eventReceiver);
		map = with<entity::Map>::spawn(tx, {width, height});
		_LOG_DEBUG_("created Map, waiting for Scoped Transactions emit message...");
	}

	void World::spawnSwordsman(UnitId id, const composition::Swordsman::Actions::SpawnParameters& parameters)
	{
		Transaction tx(state, eventReceiver);
		// check if caller wants to replace unit
		//with<entity::Unit>::remove(state, id);
		//core::operations::normalize(state);
		registeredUnits.push_back(with<composition::Swordsman>::spawn(tx, parameters));
	}

	void World::march(UnitId externalUnitId, Position target)
	{
		const auto registered = std::ranges::find(registeredUnits, externalUnitId);
		if (registered == registeredUnits.end())
			return;

		Transaction tx(state, eventReceiver);
		with<effect::OrderedToMove>::order(tx, *registered, target);
	}

	bool World::isGameOver() const
	{
		// debug-mode exit:
		if (currentTurn > 1000)
		{
			//throw std::logic_error("world is too old, something gone wrong");
			std::cout << "world looks hanged (1000 turns passed)" << std::endl;
			return true;
		}

		// this implementation makes experimental model equal to initial test assignment model
		// better add other "end game" criteria, or we will kill the world only because of
		// all units taking rest :)
		return state.line<effect::OrderedToMove>().elements.empty();
	}

	void World::step()
	{
		_INCOMPLETE_;
	}
}
