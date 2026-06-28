#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Game/Abilities/RangedAttack.h"
#include "NewGame/Game/Effects/Poisoned.h"

namespace swexp::game::ability
{
    using namespace swexp::core::api;

    struct PoisonArrows : Extension<PoisonArrows, ability::RangedAttack> {
        using Chance = uint32_t;

        struct State {
            Chance chance;
            effect::Poisoned::Damage damage;
            uint32_t duration{5};
        };

        struct Actions final : BaseActions {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
