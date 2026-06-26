#pragma once

#include "NewGame/Core/Space.h"
#include "NewGame/Core/Types.h"

namespace sw
{
	class EventSystem;
}

namespace sw::game
{
	using namespace sm::game::basic;
	class World
	{
	public:
		explicit World(EventSystem&);

		void createMap(uint32_t, uint32_t);

		void spawnUnit(UnitId, Position, uint32_t, uint32_t, uint32_t, uint32_t);

		void march(uint32_t, Position);

		[[nodiscard]]
		bool isGameOver() const;

		void step();
	};
}
