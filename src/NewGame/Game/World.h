#pragma once

#include "NewGame/Core/Interface/features.api.h"

// requred features
#include "NewGame/Features/Map.h"

namespace swexp::game::features
{
    // standard api mapping
    //namespace core = swexp::core::api;
    using namespace swexp::core::api;

    struct World : Entity<World> {
        struct State {
            using Turn = uint32_t;

            Map::Id map;
        };
        struct Logic final : BaseLogic {
            static void createMap(Context, const State&);
        };

        struct Emitters final : BaseEmitters {
        };
    };
}