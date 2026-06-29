#include "NewGame/Game/Compositions/Swordsman.h"

#include <format>
#include <stdexcept>

#include "IO/interface.include.h"
#include "NewGame/Core/Mechanism/Helpers.h"
#include "NewGame/Game/Abilities/LandMovement.h"
#include "NewGame/Game/Abilities/MeleeAttack.h"
#include "NewGame/Game/Abilities/Rending.h"
#include "NewGame/Game/Entities/Unit.h"

namespace swexp::game::composition
{
    namespace ask = ::swexp::core::manipulation;

    entity::Unit::Id Swordsman::Actions::spawn(Writing writing, const SpawnParameters& parameters)
    {
        auto& draft = writing.state;

        const entity::Unit::Id unitId = parameters.externalId;
        const auto [_, inserted] = draft.line<entity::Unit>().elements.try_emplace(unitId, entity::Unit::State{parameters.unit});
        if (!inserted)
            throw std::logic_error("Swordsman::Actions::spawn: duplicate unit id");

        draft.line<ability::LandMovement>().createComponent<entity::Unit>(unitId, {});
        draft.line<ability::MeleeAttack>().createComponent<entity::Unit>(
            unitId, ability::MeleeAttack::State{parameters.melee});
        draft.line<ability::Rending>().createComponent<entity::Unit>(
            unitId, ability::Rending::State{parameters.rending});

        const auto swordsmanNumber = draft.line<Swordsman>().elements.size() + 1;
        draft.line<Swordsman>().createComponent<entity::Unit>(
            unitId, State{.name = std::format("Swordsman#{}", swordsmanNumber)});

        return unitId;
    }

    void Swordsman::Emitters::_generated_call_all(Emitting emitting)
    {
        unitSpawned(emitting);
    }

    void Swordsman::Emitters::unitSpawned(Emitting emitting)
    {
        const auto& initial = emitting.initial.state;
        const auto& updated = emitting.updated.state;

        for (const auto id : swexp::core::mechanism::helpers::findAdded<Swordsman>(initial, updated))
        {
            const auto& unitState = ask::get<entity::Unit>(emitting.updated, id);

            emitting.listener.event(0, sw::io::UnitSpawned{
                .unitId = id,
                .unitType = "swordsman",
                .x = unitState.position.x,
                .y = unitState.position.y,
            });
        }
    }
}
