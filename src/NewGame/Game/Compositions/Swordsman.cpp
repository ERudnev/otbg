#include "NewGame/Game/Compositions/Swordsman.h"

#include "NewGame/Game/Abilities/LandMovement.h"
#include "NewGame/Game/Abilities/MeleeAttack.h"
#include "NewGame/Game/Abilities/Rending.h"
#include "NewGame/Game/Entities/Unit.h"

namespace swexp::game::composition
{
    entity::Unit::Id Swordsman::Actions::spawn(Writing writing, const SpawnParameters& parameters)
    {
        auto& draft = writing.state;

        const entity::Unit::Id unitId = draft.line<entity::Unit>().createEntity(
            entity::Unit::State{parameters.unit});

        draft.line<ability::LandMovement>().createComponent<entity::Unit>(unitId, {});
        draft.line<ability::MeleeAttack>().createComponent<entity::Unit>(
            unitId, ability::MeleeAttack::State{parameters.melee});
        draft.line<ability::Rending>().createComponent<entity::Unit>(
            unitId, ability::Rending::State{parameters.rending});
        draft.line<Swordsman>().createComponent<entity::Unit>(unitId, {});

        return unitId;
    }
}
