#pragma once

#include "NewGame/Core/Interface/features.api.h"

// Root-level Game Logic types
namespace swexp::game::entity
{
    // standard api mapping
    //namespace core = swexp::core::api;
    using namespace swexp::core::api;

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
        struct Logic final : BaseLogic {
            static Id create(Context, const State&);
        };

        struct Emitters final : BaseEmitters {
        };
    };
}