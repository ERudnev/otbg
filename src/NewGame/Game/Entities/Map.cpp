#include "NewGame/Game/Entities/Map.h"

#include "IO/interface.include.h"
#include "NewGame/Core/Mechanism/Helpers.h"

namespace swexp::game::entity
{

    auto Map::Actions::spawn(Writing writing, const State& state) -> Id
    {
        return writing.state.line<Map>().createEntity(Map::State{state});
    }

    void Map::Emitters::_generated_call_all(Emitting emitting)
    {
        mapCreated(emitting);
    }

    void Map::Emitters::mapCreated(Emitting emitting)
    {
        const auto& initial = emitting.initial.state;
        const auto& updated = emitting.updated.state;

        for (const auto id : swexp::core::mechanism::helpers::findAddedOrUpdated<Map>(initial, updated))
        {
            const auto& mapState = updated.line<Map>().elements.at(id);

            _LOG_DEBUG_("Emitting Map Created");
            emitting.listener.event(0, sw::io::MapCreated{
                .width = mapState.width,
                .height = mapState.height,
            });
        }
    }
}
