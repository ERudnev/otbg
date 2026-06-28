#include "Session.h"

#include "Core/Model/Intertype.h"
#include "IO/interface.include.h"
#include "NewGame/Core/Interface/macros.h"

namespace swexp::game
{

	// priate Schema init:
	using namespace swexp::core::api;

	inline Schema createSchema() {
		using namespace entity;
		return core::model::intertype::SchemaData::build<
			World,
			Map
		>();
	}


	Session::Session(sw::EventSystem& events)
		: eventReceiver(events)
		, schema(createSchema())
		, state(schema)
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
