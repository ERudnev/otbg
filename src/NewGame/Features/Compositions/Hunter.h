#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Features/Entities/Unit.h"
#include "NewGame/Features/Abilities/LandMovement.h"
#include "NewGame/Features/Abilities/MeleeAttack.h"
#include "NewGame/Features/Abilities/RangedAttack.h"
#include "NewGame/Features/Abilities/PoisonArrows.h"

namespace swexp::game::composition
{
    using namespace swexp::core::api;

    struct Hunter : Extension<Hunter, entity::Unit> {
        struct State {
            // TODO: add ability control state here. For example cooldowns, disruptions, e.t.c
        };

        struct Actions final : BaseActions {
            struct SpawnParameters {
                entity::Unit::Id externalId;
                entity::Map::Position position;
                entity::Unit::HitPoints hitPoints;
                ability::RangedAttack::State ranged;
                ability::MeleeAttack::State melee;
                ability::PoisonArrows::State poisonArrows;
            };

            static auto spawn(Writing, const SpawnParameters&) -> entity::Unit::Id;
            static bool makeTurn(Writing, Id);
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
