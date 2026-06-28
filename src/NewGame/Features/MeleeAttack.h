#pragma once

#include "NewGame/Core/Interface/features.api.h"

namespace swexp::game::entity
{
    using namespace swexp::core::api;

    struct MeleeAttack : Entity<MeleeAttack> {
        using Strength = uint32_t;

        struct State {
            Strength strength;
        };

        struct Logic final : BaseLogic {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
