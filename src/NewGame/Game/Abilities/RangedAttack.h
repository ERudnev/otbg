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
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
