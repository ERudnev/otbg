#pragma once

#include "NewGame/Core/Interface/features.api.h"

// Root-level Game Logic types
namespace swexp::game::entity
{
    // standard api mapping
    //namespace core = swexp::core::api;
    using namespace swexp::core::api;

    // NB: only Space, does not know about occupancy. See entity::Body for occupancy map
    struct Map : Entity<Map> {
        struct Position
        {
            uint32_t x{0};
            uint32_t y{0};

            friend bool operator==(const Position&, const Position&) = default;
        };

        struct State {
            uint32_t width;
            uint32_t height;

            friend bool operator==(const State&, const State&) = default;
        };
        struct Actions final : BaseActions {
            static auto spawn(Writing, const State&)->Id;
        };

        struct Reactions final : BaseReactions {
            static Summary _generated_call_all(Reacting) { return 0; }
        };

        struct Emitters final : BaseEmitters {
            static void _generated_call_all(Emitting);
            static void mapCreated(Emitting emitting);
        };
    };
}