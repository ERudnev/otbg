#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Logic/Entities/Unit.h"

namespace swexp::game::ability
{
    using namespace swexp::core::api;

    struct Rending : Extension<Rending, entity::Unit> {
        using Chance = uint32_t;
        using Damage = entity::Unit::HitPoints;

        struct State {
            Chance chance;
            Damage damage;
        };

        struct Logic final : BaseLogic {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
