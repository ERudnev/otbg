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
        };

        struct Actions final : BaseActions {
        };

        struct Emitters final : BaseEmitters {
            static void _generated_call_all(Emitting) {}
        };
    };
}
