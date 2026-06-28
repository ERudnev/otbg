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
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
