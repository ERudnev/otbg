#pragma once

#include "NewGame/Game/Types.h"

namespace sw
{
	class EventSystem;
}

// TODO: this class will go to Core one day... it is loosing all game logic becoming just Dispatcher...
namespace swexp::game
{
	// inject basic types:
	using namespace ::swexp::game::types;

	// Acts as Game interface to the IO and Events
	class Session
	{
	public:
		explicit Session(sw::EventSystem&);

		void createMap(uint32_t, uint32_t);

		// TODO: refactor with unit classes: {HP+Pos+HP} + C1{S, C, R}
		void spawnUnit(UnitId, Position, HitPoints, Strength, Chance, Rending);

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


	};
}
