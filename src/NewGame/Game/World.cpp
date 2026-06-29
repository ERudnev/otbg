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
	namespace ask = ::swexp::core::manipulation;

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
		actionsLastTurn = 1;
		map = state.line<entity::Map>().createEntity({0,0});
	}

	void World::createMap(uint32_t width, uint32_t height)
	{
		Transaction tx(state, core::ReportingContext{currentTurn, &eventReceiver});
		map = with<entity::Map>::spawn(tx, {width, height});
	}

	void World::spawnSwordsman(UnitId id, const composition::Swordsman::Actions::SpawnParameters& parameters)
	{
		Transaction tx(state, core::ReportingContext{currentTurn, &eventReceiver});
		// check if caller wants to replace unit
		//with<entity::Unit>::remove(state, id);
		//core::operations::normalize(state);
		registeredUnits.push_back(with<composition::Swordsman>::spawn(tx, parameters));
	}

	void World::spawnHunter(UnitId id, const composition::Hunter::Actions::SpawnParameters& parameters)
	{
		Transaction tx(state, core::ReportingContext{currentTurn, &eventReceiver});
		registeredUnits.push_back(with<composition::Hunter>::spawn(tx, parameters));
	}

	void World::march(UnitId externalUnitId, Position target)
	{
		const auto registered = std::ranges::find(updatedList(registeredUnits), externalUnitId);
		if (registered == registeredUnits.end())
			return;

		Transaction tx(state, core::ReportingContext{currentTurn, &eventReceiver});
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

		return currentTurn > 0 and actionsLastTurn == 0;
	}

	const std::vector<swexp::game::api::UnitId>& World::updatedList(std::vector<swexp::game::api::UnitId>& buffer)
	{
		const auto source = registeredUnits;

		buffer.clear();
		buffer.reserve(source.size());

		for (const auto unitId : source)
		{
			if (ask::exists<entity::Unit>(Reading{state, core::ReportingContext{currentTurn, &eventReceiver}}, unitId))
				buffer.push_back(unitId);
		}

		return buffer;
	}

	size_t World::updateEffects(Writing writing)
	{
		size_t updatedEffects = 0;
		updatedEffects += with<effect::Poisoned>::updateEffect(writing);
		updatedEffects += with<effect::Rended>::updateEffect(writing);
		return updatedEffects;
	}

	size_t World::applyEffects(Writing writing)
	{
		size_t applied = 0;
		applied += with<effect::Poisoned>::applyEffect(writing);
		return applied;
	}

	void World::step()
	{
		++currentTurn;
		actionsLastTurn = 0;

		// Phase 1: update existing effects
		{
			Transaction tx(state, core::ReportingContext{currentTurn, &eventReceiver});
			actionsLastTurn += updateEffects(tx);
		}

		// Phase 2: let every registered unit spend its own turn strategy.
		// The world is responsible only for the order of dispatch.
		std::vector<UnitId> aliveUnits;
		for (const auto unitId : updatedList(aliveUnits))
		{
			Transaction tx(state, core::ReportingContext{currentTurn, &eventReceiver});
			if (with<entity::Unit>::makeTurn(tx, unitId))
				++actionsLastTurn;
		}

		// Phase 3: later this is a good place for world-owned post-processing.
		{
			Transaction tx(state, core::ReportingContext{currentTurn, &eventReceiver});
			actionsLastTurn += applyEffects(tx);
		}

		// Examples: cleanup of dead references, global effects, turn-wide rules.

		// Phase 4: transaction destructor will normalize state and emit events.
	}
}
