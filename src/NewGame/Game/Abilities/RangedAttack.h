#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Game/Entities/Unit.h"

namespace swexp::game::ability
{
    using namespace swexp::core::api;

    struct RangedAttack : Extension<RangedAttack, entity::Unit> {
        using Range = uint32_t;

        struct State {
            Range minRange{2};
            Range maxRange;
            uint32_t damage;
        };

        struct Actions final : BaseActions {
            static void attack(Writing, Id attackerId, entity::Unit::Id targetId);
        };

        struct Reactions final : BaseReactions {
            static Summary _generated_call_all(Reacting) { return 0; }
        };

        struct Emitters final : BaseEmitters {
            static void _generated_call_all(Emitting) {}
        };
    };
}
