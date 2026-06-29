#pragma once

#include <string>

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Game/_types.exports.h"
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
                ::swexp::game::api::UnitId externalId;
                entity::Map::Position position;
                entity::Unit::HitPoints hitPoints;
                ability::MeleeAttack::State melee;
                ability::Rending::State rending;
            };
            static entity::Unit::Id spawn(Writing, const SpawnParameters&);
            static bool makeTurn(Writing, Id); // NB: Swordsman::Id == Unit::Id; true means "turn was spent"
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
