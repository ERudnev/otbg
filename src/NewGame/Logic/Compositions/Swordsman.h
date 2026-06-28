#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Logic/Abilities/Rending.h"
#include "NewGame/Logic/Entities/Unit.h"
#include "NewGame/Logic/Abilities/LandMovement.h"
#include "NewGame/Logic/Abilities/MeleeAttack.h"
#include "NewGame/Logic/Abilities/Rending.h"

namespace swexp::game::composition
{
    using namespace swexp::core::api;

    struct Swordsman : Extension<Swordsman, entity::Unit> {
        struct State {
            // TODO: cleanup this comments before release

            // not needed: eing Extension of Unit has own Id value == Unit' Id value
            // Unit::Id unit;

            // same (Transitivity) ability::Movement::Id movement;
            // same (Transitivity) ability::MeleeAttack::Id meleeAttack;
            // same (Transitivity) ability::Rending::Id rending;
        };

        struct Logic final : BaseLogic {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
