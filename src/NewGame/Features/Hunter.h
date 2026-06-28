#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Features/Body.h"
#include "NewGame/Features/Movement.h"
#include "NewGame/Features/MeleeAttack.h"
#include "NewGame/Features/RangedAttack.h"
#include "NewGame/Features/PoisonArrows.h"

namespace swexp::game::entity
{
    using namespace swexp::core::api;

    struct Hunter : Entity<Hunter> {
        struct State {
            Body::Id body;
            Movement::Id movement;
            MeleeAttack::Id meleeAttack;
            RangedAttack::Id rangedAttack;
            PoisonArrows::Id poisonArrows;
        };

        struct Logic final : BaseLogic {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
