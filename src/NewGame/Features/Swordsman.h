#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Features/Body.h"
#include "NewGame/Features/Movement.h"
#include "NewGame/Features/MeleeAttack.h"
#include "NewGame/Features/RendingAbility.h"

namespace swexp::game::entity
{
    using namespace swexp::core::api;

    struct Swordsman : Entity<Swordsman> {
        struct State {
            Body::Id body;
            Movement::Id movement;
            MeleeAttack::Id meleeAttack;
            RendingAbility::Id rendingAbility;
        };

        struct Logic final : BaseLogic {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
