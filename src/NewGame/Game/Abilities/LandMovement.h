#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Game/Entities/Unit.h"

namespace swexp::game::ability
{
    using namespace swexp::core::api;

    struct LandMovement : Extension<LandMovement, entity::Unit> {
        struct State {
            uint32_t stepDistance{1};
            // TODO: add movement-impared effects landing data here
            // example: bool suppressed = false;
            // this will allow effects-on-abilities transapent to abilitity logic
        };

        struct Actions final : BaseActions {
        };

        struct Emitters final : BaseEmitters {
            static void _generated_call_all(Emitting) {}
        };
    };
}
