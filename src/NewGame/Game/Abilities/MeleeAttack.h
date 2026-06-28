#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Game/Entities/Unit.h"

namespace swexp::game::ability
{
    using namespace swexp::core::api;

    struct MeleeAttack : Extension<MeleeAttack, entity::Unit> {
        using Strength = uint32_t;

        struct State {
            Strength strength;
        };

        struct Actions final : BaseActions {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
