#pragma once

#include <functional>

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Game/Entities/Map.h"

namespace swexp::game::entity
{
    using namespace swexp::core::api;

    struct Unit : Entity<Unit> {
        using HitPoints = uint32_t;
        using TurnStrategy = std::function<bool(core::api::context::Writing, Id)>;

        struct State {
            Map::Position position;
            HitPoints hitPoints;
            TurnStrategy turnStrategy;
        };

        struct Actions final : BaseActions {
            // replacement of original sw::game::Map::_positionByUnitId
            static auto findOccupying(Reading, Map::Position)->Id;
            static bool makeTurn(Writing, Id); // returns "turn was spent"; false means idle
        };

        struct Reactions final : BaseReactions {
            static Summary _generated_call_all(Reacting) { return 0; }
        };

        struct Emitters final : BaseEmitters {
            static void _generated_call_all(Emitting) {}
        };
    };
}
