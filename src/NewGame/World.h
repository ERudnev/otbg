#pragma once

#include <vector>

#include "NewGame/Core/Operations/_forwards.h"
#include "NewGame/Core/Mechanism/ScopedTransaction.h"
#include "NewGame/Core/Interface/features.api.h"
// TODO: convert World to private-implemented to avoid of this includes
#include "NewGame/Core/Model/Complex.h"
// Logic layer
#include "NewGame/Features/_types.exports.h"

// this include must be removed with SpawnType exported
#include "NewGame/Features/Compositions/Hunter.h"
#include "NewGame/Features/Compositions/Swordsman.h"

namespace sw
{
	class EventSystem;
}

// TODO: this class will be moved to the Core one day... (Dispatcher?)
namespace swexp::game
{
	// inject basic types:
	using namespace ::swexp::game::api;
	using namespace ::swexp::core::api;

	// Acts as Game interface to the IO and Events
	class World
	{
	public:
		using Turn = uint32_t;

		explicit World(sw::EventSystem&);

		void createMap(uint32_t, uint32_t);

		// TODO: refactor with unit classes: {HP+Pos+HP} + C1{S, C, R}
		void spawnSwordsman(UnitId, const composition::Swordsman::Actions::SpawnParameters&);
		void spawnHunter(UnitId, const composition::Hunter::Actions::SpawnParameters&);

		void march(UnitId, Position);

		[[nodiscard]]
		bool isGameOver() const;

		void step();
	private:
		/* CLEANUP reminder:
		Map _map;
		EventSystem& _events;
		std::vector<Unit> _units;
		uint32_t _tick;
		*/

		sw::EventSystem& eventReceiver;
		Schema schema;
		core::model::complex::State state;

		// own state:
		Turn currentTurn{0};
		size_t actionsLastTurn{1};
        entity::Map::Id map;
		std::vector<UnitId> registeredUnits;

		// private using as bringe to Entity::Actions interface
		// this makes World as "Entity with Actions"
		using Reading = core::api::context::Reading;
        using Writing = core::api::context::Writing;
		using Transaction = core::mechanism::ScopedTransaction;

		size_t updateEffects(Writing);
		size_t applyEffects(Writing);
		const std::vector<swexp::game::api::UnitId>& updatedList(std::vector<swexp::game::api::UnitId>&);
	};
}
