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
            static bool tryApply(Writing, Id applierId, entity::Unit::Id targetId);
        };

        struct Reactions final : BaseReactions {
            static Summary _generated_call_all(Reacting) { return 0; }
        };

        struct Emitters final : BaseEmitters {
            static void _generated_call_all(Emitting) {}
        };
    };
}
