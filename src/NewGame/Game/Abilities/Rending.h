#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Game/Entities/Unit.h"

namespace swexp::game::ability
{
    using namespace swexp::core::api;

    struct Rending : Extension<Rending, entity::Unit> {
        using Chance = uint32_t;
        using Amount = entity::Unit::HitPoints;

        struct State {
            Chance chance;
            Amount damage;
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
