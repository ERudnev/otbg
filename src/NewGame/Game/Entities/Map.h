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
        };

        struct State {
            uint32_t width;
            uint32_t height;
        };
        struct Actions final : BaseActions {
            static auto create(Writing, const State&)->Id;
        };

        struct Emitters final : BaseEmitters {
        };
    };
}