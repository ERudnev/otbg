#pragma once

#include "NewGame/Game/Types.h"

namespace sw
{
	class EventSystem;
}

namespace swexp::game
{
	// inject basic types:
	using namespace ::swexp::game::types;

	// Acts as Game interface to the IO and Events
	class World
	{
	public:
		explicit World(sw::EventSystem&);

		void createMap(uint32_t, uint32_t);

		// TODO: refactor with unit classes: {HP+Pos+HP} + C1{S, C, R}
		void spawnUnit(UnitId, Position, HitPoints, Strength, Chance, Rending);

		void march(UnitId, Position);

		[[nodiscard]]
		bool isGameOver() const;

		void step();
	private:

	};
}
