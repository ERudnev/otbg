#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Game/Entities/Unit.h"
#include "NewGame/Game/Abilities/LandMovement.h"
#include "NewGame/Game/Abilities/MeleeAttack.h"
#include "NewGame/Game/Abilities/RangedAttack.h"
#include "NewGame/Game/Abilities/PoisonArrows.h"

namespace swexp::game::composition
{
    using namespace swexp::core::api;

    struct Hunter : Extension<Hunter, entity::Unit> {
        struct State {
            // TODO: add ability control state here. For example cooldowns, disruptions, e.t.c
        };

        struct Actions final : BaseActions {
        };

        struct Reactions final : BaseReactions {
            static Summary _generated_call_all(Reacting) { return 0; }
        };

        struct Emitters final : BaseEmitters {
            static void _generated_call_all(Emitting) {}
        };
    };
}
