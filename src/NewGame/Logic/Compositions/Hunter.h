#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Logic/Entities/Unit.h"
#include "NewGame/Logic/Abilities/LandMovement.h"
#include "NewGame/Logic/Abilities/MeleeAttack.h"
#include "NewGame/Logic/Abilities/RangedAttack.h"
#include "NewGame/Logic/Abilities/PoisonArrows.h"

namespace swexp::game::composition
{
    using namespace swexp::core::api;

    struct Hunter : Extension<Hunter, entity::Unit> {
        struct State {
            // TODO: add ability control state here. For example cooldowns, disruptions, e.t.c
        };

        struct Logic final : BaseLogic {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
