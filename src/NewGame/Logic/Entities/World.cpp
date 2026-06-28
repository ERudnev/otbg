#include "NewGame/Logic/Entities/World.h"

#include "NewGame/Core/Logic/ContextData.h"

namespace swexp::game::entity
{
    void World::Logic::createMap(Writing writing, Id id, const Map::Position& size)
    {
        _LOG_DEBUG_("create map reached (OK)");
        auto& me = Get(writing, id);

        /*
        auto& world = wrting.state.line<Map>
        auto& maps = writing.state.elements<Map>();
        const Map::Id mapId = static_cast<Map::Id>(maps.elements.size());
        maps.elements.emplace(mapId, Map::State{.width = size.x, .height = size.y});

        auto& worlds = writing.state.elements<World>();
        if (worlds.elements.empty())
        {
            worlds.elements.emplace(
                World::Id{0},
                World::State{.currentTurn = 0, .map = mapId});
            return;
        }

        for (auto& [_, worldState] : worlds.elements)
        {
            worldState.map = mapId;
        }
        */
    }
}
