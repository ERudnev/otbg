#include "World.h"

#include "IO/interface.include.h"
#include "NewGame/Core/Interface/macros.h"

namespace swexp::game
{
	World::World(sw::EventSystem&)
	{
		_INCOMPLETE_;
	}

	void World::createMap(uint32_t, uint32_t)
	{
		_INCOMPLETE_;
	}

	void World::spawnUnit(uint32_t, Position, uint32_t, uint32_t, uint32_t, uint32_t)
	{
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
