#include "NewGame/Features/Compositions/Swordsman.h"

#include <format>
#include <stdexcept>

#include "IO/interface.include.h"
#include "NewGame/Core/Mechanism/Helpers.h"
#include "NewGame/Features/Abilities/LandMovement.h"
#include "NewGame/Features/Abilities/MeleeAttack.h"
#include "NewGame/Features/Abilities/Rending.h"
#include "NewGame/Features/Effects/OrderedToMove.h"
#include "NewGame/Features/Entities/Unit.h"

namespace swexp::game::composition
{
    namespace ask = ::swexp::core::manipulation;

    entity::Unit::Id Swordsman::Actions::spawn(Writing writing, const SpawnParameters& parameters)
    {
        auto& draft = writing.state;

        const entity::Unit::Id unitId = parameters.externalId;
        const auto [_, inserted] = draft.line<entity::Unit>().elements.try_emplace(
                unitId,
                entity::Unit::State{
                        .position = parameters.position,
                        .hitPoints = parameters.hitPoints,
                        .turnStrategy = &makeTurn,
                });
        if (not inserted)
        {
            throw std::logic_error("Swordsman::Actions::spawn: duplicate unit id");
        }

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

    bool Swordsman::Actions::makeTurn(Writing writing, Id id)
    {
        // Runtime shortcut: current prototype assumes the newest map is the active battlefield.
        const auto& maps = writing.state.line<entity::Map>().elements;
        if (maps.empty())
        {
            return false;
        }

        entity::Map::Id mapId = maps.begin()->first;
        for (const auto& [candidateId, _] : maps)
        {
            if (candidateId > mapId)
            {
                mapId = candidateId;
            }
        }

        auto unit = ask::try_get<entity::Unit>(writing, id);
        if (not unit)
        {
            return false;
        }

        // Swordsman policy matches the reference world: attack adjacent live targets before moving.
        std::vector<uint32_t> targetUnitIds;
        entity::Map::Actions::findTargets(writing, mapId, id, unit->position, targetUnitIds);

        for (const auto targetUnitId : targetUnitIds)
        {
            auto target = ask::try_get<entity::Unit>(writing, targetUnitId);
            if (not target or target->hitPoints == 0)
            {
                continue;
            }

            if (not ability::Rending::Actions::tryApply(writing, id, targetUnitId))
            {
                ability::MeleeAttack::Actions::attack(writing, id, targetUnitId);
            }

            target = ask::try_get<entity::Unit>(writing, targetUnitId);
            if (target and target->hitPoints == 0)
            {
                writing.reporting.system->event(
                        writing.reporting.currentTurn,
                        sw::io::UnitDied{
                                .unitId = targetUnitId,
                        });
                writing.state.line<entity::Unit>().elements.erase(targetUnitId);
            }

            return true;
        }

        // No adjacent target: try to advance along the current move order.
        auto order = ask::try_get<effect::OrderedToMove>(writing, id);
        if (not order)
        {
            return false;
        }

        const auto targetPosition = order->targetPosition;
        entity::Map::Position nextPosition;
        bool moved = false;
        if (entity::Map::Actions::tryGetNextPosition(writing, mapId, unit->position, targetPosition, nextPosition))
        {
            unit->position = nextPosition;
            moved = true;
            writing.reporting.system->event(
                    writing.reporting.currentTurn,
                    sw::io::UnitMoved{
                            .unitId = id,
                            .x = nextPosition.x,
                            .y = nextPosition.y,
                    });
        }

        bool marchEnded = false;
        if (unit->position == targetPosition)
        {
            writing.state.line<effect::OrderedToMove>().elements.erase(id);
            marchEnded = true;
        }

        return moved or marchEnded;
    }

    void Swordsman::Emitters::_generated_call_all(Emitting emitting) { unitSpawned(emitting); }

    void Swordsman::Emitters::unitSpawned(Emitting emitting)
    {
        const auto& initial = emitting.initial.state;
        const auto& updated = emitting.updated.state;

        for (const auto id : swexp::core::mechanism::helpers::findAdded<Swordsman>(initial, updated))
        {
            const auto& unitState = ask::get<entity::Unit>(emitting.updated, id);

            emitting.reporting.system->event(
                    emitting.reporting.currentTurn,
                    sw::io::UnitSpawned{
                            .unitId = id,
                            .unitType = "swordsman",
                            .x = unitState.position.x,
                            .y = unitState.position.y,
                    });
        }
    }
}
