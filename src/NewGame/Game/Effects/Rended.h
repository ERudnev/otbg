#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Game/Entities/Unit.h"

namespace swexp::game::effect
{
    using namespace swexp::core::api;

    struct Rended : Effect<Rended, entity::Unit> {
        using Damage = entity::Unit::HitPoints;

        struct State {
            entity::Unit::Id applier;
            Damage damage;
            uint32_t remainingTurns;
        };

        struct Actions final : BaseActions {
            static size_t updateEffect(Writing);
        };

        struct Reactions final : BaseReactions {
            static Summary _generated_call_all(Reacting) { return 0; }
        };

        struct Emitters final : BaseEmitters {
            static void _generated_call_all(Emitting) {}
        };
    };
}
