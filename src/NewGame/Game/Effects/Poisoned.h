#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Game/Entities/Unit.h"

namespace swexp::game::effect
{
    using namespace swexp::core::api;

    struct Poisoned : Effect<Poisoned, entity::Unit> {
        using Damage = entity::Unit::HitPoints;

        struct State {
            entity::Unit::Id applier;
            Damage damageBudgetRemaining;
            uint32_t remainingTurns;
        };

        struct Actions final : BaseActions {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
