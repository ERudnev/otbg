#pragma once

#include "NewGame/Core/Interface/features.api.h"

namespace swexp::game::entity
{
    using namespace swexp::core::api;

    struct RendingAbility : Entity<RendingAbility> {
        using Chance = uint32_t;
        using Rending = uint32_t;

        struct State {
            Chance chance;
            Rending rending;
        };

        struct Logic final : BaseLogic {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
