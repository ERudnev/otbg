#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Logic/Entities/Map.h"

namespace swexp::game::entity
{
    using namespace swexp::core::api;

    struct Unit : Entity<Unit> {
        using HitPoints = uint32_t;

        struct State {
            Map::Position position;
            HitPoints hitPoints;
        };

        struct Logic final : BaseLogic {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
