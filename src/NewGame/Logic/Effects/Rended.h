#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Logic/Entities/Unit.h"

namespace swexp::game::effect
{
    using namespace swexp::core::api;

    struct Rended : Effect<Rended, entity::Unit> {
        using Damage = entity::Unit::HitPoints;

        struct State {
            entity::Unit::Id applier;
            Damage damage;
        };

        struct Logic final : BaseLogic {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
