#include "NewGame/Game/Entities/Map.h"

namespace swexp::game::entity
{
    auto Map::Actions::spawn(Writing writing, const State& state) -> Id
    {
        return writing.state.line<Map>().createEntity(Map::State{state});
    }
}
