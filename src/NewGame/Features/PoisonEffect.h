#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Features/Body.h"

namespace swexp::game::entity
{
    using namespace swexp::core::api;

    struct PoisonEffect : Entity<PoisonEffect> {
        using Poison = uint32_t;

        struct State {
            Body::Id applier;
            Poison poison;
            uint32_t remainingTurns;
            bool doublesOnRending{true};
        };

        struct Logic final : BaseLogic {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
