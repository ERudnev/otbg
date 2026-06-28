#pragma once

#include "NewGame/Core/Interface/features.api.h"

namespace swexp::game::entities
{
    // standard api mapping
    //namespace core = swexp::core::api;
    using namespace swexp::core::api;

    struct Map : Entity<Map> {
        struct State {
            //TODO: consider integer vector2 form here
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