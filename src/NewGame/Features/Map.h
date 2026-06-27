#pragma once

#include "NewGame/Core/Interface/features.api.h"

namespace swexp::game::features
{
    // standard api mapping
    //namespace core = swexp::core::api;
    using namespace swexp::core::api;

    struct Map : Feature<Map> {
        struct State {
            //TODO: consider integer vector2 form here
            uint32_t width;
            uint32_t height;
        };
        struct Operations final : BaseOperations {
            static Id create(Context, const State&);
        };
        struct Rules final : BaseRules {
            Rules();
        };
        struct Emitters final : BaseEmitters {
        };
    };
}