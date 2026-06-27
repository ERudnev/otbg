#include "Session.h"

#include "IO/interface.include.h"
#include "NewGame/Core/Interface/macros.h"

namespace swexp::game
{
	Session::Session(sw::EventSystem& events)
		: eventReceiver(events)
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
