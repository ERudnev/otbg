#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Features/PoisonEffect.h"
#include "NewGame/Features/RendingAbility.h"

namespace swexp::game::entity
{
    using namespace swexp::core::api;

    struct PoisonArrows : Entity<PoisonArrows> {
        struct State {
            RendingAbility::Chance chance;
            PoisonEffect::Poison poison;
            uint32_t duration{5};
        };

        struct Logic final : BaseLogic {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
