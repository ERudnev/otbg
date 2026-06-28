#pragma once

#include "NewGame/Core/Interface/features.api.h"

namespace swexp::game::entity
{
    using namespace swexp::core::api;

    struct RangedAttack : Entity<RangedAttack> {
        using Range = uint32_t;

        struct State {
            Range minRange{2};
            Range maxRange;
            uint32_t damage;
        };

        struct Logic final : BaseLogic {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
