#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Game/Entities/Map.h"

namespace swexp::game::entity
{
    using namespace swexp::core::api;

    struct Unit : Entity<Unit> {
        using HitPoints = uint32_t;

        struct State {
            Map::Position position;
            HitPoints hitPoints;
        };

        struct Actions final : BaseActions {
            // replacement of original sw::game::Map::_positionByUnitId
            static auto findOccupying(Reading, Map::Position)->Id;
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
