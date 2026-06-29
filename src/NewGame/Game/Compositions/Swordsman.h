#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Game/Abilities/Rending.h"
#include "NewGame/Game/Entities/Unit.h"
#include "NewGame/Game/Abilities/LandMovement.h"
#include "NewGame/Game/Abilities/MeleeAttack.h"
#include "NewGame/Game/Abilities/Rending.h"

namespace swexp::game::composition
{
    using namespace swexp::core::api;

    struct Swordsman : Composition<Swordsman, entity::Unit> {
        struct State {
            // TODO: cleanup this comments before release

            // not needed: eing Extension of Unit has own Id value == Unit' Id value
            // Unit::Id unit;

            // same (Transitivity) ability::Movement::Id movement;
            // same (Transitivity) ability::MeleeAttack::Id meleeAttack;
            // same (Transitivity) ability::Rending::Id rending;
        };

        struct Actions final : BaseActions {
            struct SpawnParameters {
                entity::Unit::State unit;
                ability::MeleeAttack::State melee;
                ability::Rending::State rending;
            };
            static entity::Unit::Id spawn(Writing, const SpawnParameters&);
        };

        struct Reactions final : BaseReactions {

        };

        struct Emitters final : BaseEmitters {
        };
    };
}
