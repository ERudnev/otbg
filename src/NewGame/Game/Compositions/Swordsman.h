#pragma once

#include <string>

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
            std::string name;
            // if you want control your abilities, skill levels, e.t.x. - add parameters here!
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
            static Summary _generated_call_all(Reacting) { return 0; }
        };

        struct Emitters final : BaseEmitters {
            static void _generated_call_all(Emitting);
            static void unitSpawned(Emitting);
        };
    };
}
