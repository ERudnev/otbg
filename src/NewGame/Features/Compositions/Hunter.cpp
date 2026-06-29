#include "NewGame/Features/Compositions/Hunter.h"

#include <format>
#include <vector>

#include "IO/interface.include.h"
#include "NewGame/Core/Interface/InjectedRandomDevice.h"
#include "NewGame/Core/Manipulation/Helpers.h"
#include "NewGame/Core/Mechanism/Helpers.h"
#include "NewGame/Features/Abilities/MeleeAttack.h"
#include "NewGame/Features/Abilities/PoisonArrows.h"
#include "NewGame/Features/Abilities/RangedAttack.h"
#include "NewGame/Features/Effects/OrderedToMove.h"
#include "NewGame/Features/Entities/Map.h"

namespace swexp::game::composition
{
    namespace ask = ::swexp::core::manipulation;

    namespace
    {
        bool isInRangedWindow(entity::Map::Position from, entity::Map::Position to, ability::RangedAttack::Range minRange, ability::RangedAttack::Range maxRange)
        {
            const auto dx = from.x > to.x ? from.x - to.x : to.x - from.x;
            const auto dy = from.y > to.y ? from.y - to.y : to.y - from.y;
            const auto distance = std::max(dx, dy);
            return distance >= minRange and distance <= maxRange;
        }
    }

    entity::Unit::Id Hunter::Actions::spawn(Writing writing, const SpawnParameters& parameters)
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
            throw std::logic_error("Hunter::Actions::spawn: duplicate unit id");

        draft.line<ability::LandMovement>().createComponent<entity::Unit>(unitId, {});
        draft.line<ability::MeleeAttack>().createComponent<entity::Unit>(
            unitId, ability::MeleeAttack::State{parameters.melee});
        draft.line<ability::RangedAttack>().createComponent<entity::Unit>(
            unitId, ability::RangedAttack::State{parameters.ranged});
        draft.line<ability::PoisonArrows>().createComponent<ability::RangedAttack>(
            unitId, ability::PoisonArrows::State{parameters.poisonArrows});

        draft.line<Hunter>().createComponent<entity::Unit>(
            unitId, State{});

        return unitId;
    }

    bool Hunter::Actions::makeTurn(Writing writing, Id id)
    {
        const auto& maps = writing.state.line<entity::Map>().elements;
        if (maps.empty())
            return false;

        entity::Map::Id mapId = maps.begin()->first;
        for (const auto& [candidateId, _] : maps)
        {
            if (candidateId > mapId)
                mapId = candidateId;
        }

        auto unit = ask::try_get<entity::Unit>(writing, id);
        if (not unit)
            return false;

        std::vector<uint32_t> adjacentTargetIds;
        entity::Map::Actions::findTargets(writing, mapId, id, unit->position, adjacentTargetIds);

        for (const auto targetUnitId : adjacentTargetIds)
        {
            auto target = ask::try_get<entity::Unit>(writing, targetUnitId);
            if (not target or target->hitPoints == 0)
                continue;

            ability::MeleeAttack::Actions::attack(writing, id, targetUnitId);

            target = ask::try_get<entity::Unit>(writing, targetUnitId);
            if (target and target->hitPoints == 0)
            {
                writing.reporting.system->event(writing.reporting.currentTurn, sw::io::UnitDied{
                    .unitId = targetUnitId,
                });
                writing.state.line<entity::Unit>().elements.erase(targetUnitId);
            }

            return true;
        }

        const auto* ranged = ask::try_get<ability::RangedAttack>(writing, id);
        if (ranged)
        {
            std::vector<entity::Unit::Id> rangedTargetIds;
            for (const auto& [targetId, targetState] : writing.state.line<entity::Unit>().elements)
            {
                if (targetId == id or targetState.hitPoints == 0)
                    continue;

                if (isInRangedWindow(unit->position, targetState.position, ranged->minRange, ranged->maxRange))
                    rangedTargetIds.push_back(targetId);
            }

            if (not rangedTargetIds.empty())
            {
                const auto randomIndex = core::interface::InjectedRandomDevice::next() % rangedTargetIds.size();
                const auto targetUnitId = rangedTargetIds[randomIndex];

                if (not ability::PoisonArrows::Actions::tryApply(writing, id, targetUnitId))
                    ability::RangedAttack::Actions::attack(writing, id, targetUnitId);

                auto target = ask::try_get<entity::Unit>(writing, targetUnitId);
                if (target and target->hitPoints == 0)
                {
                    writing.reporting.system->event(writing.reporting.currentTurn, sw::io::UnitDied{
                        .unitId = targetUnitId,
                    });
                    writing.state.line<entity::Unit>().elements.erase(targetUnitId);
                }

                return true;
            }
        }

        auto order = ask::try_get<effect::OrderedToMove>(writing, id);
        if (not order)
            return false;

        const auto targetPosition = order->targetPosition;
        entity::Map::Position nextPosition;
        bool moved = false;
        if (entity::Map::Actions::tryGetNextPosition(writing, mapId, unit->position, targetPosition, nextPosition))
        {
            unit->position = nextPosition;
            moved = true;
            writing.reporting.system->event(writing.reporting.currentTurn, sw::io::UnitMoved{
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

    void Hunter::Emitters::_generated_call_all(Emitting emitting)
    {
        unitSpawned(emitting);
    }

    void Hunter::Emitters::unitSpawned(Emitting emitting)
    {
        const auto& initial = emitting.initial.state;
        const auto& updated = emitting.updated.state;

        for (const auto id : swexp::core::mechanism::helpers::findAdded<Hunter>(initial, updated))
        {
            const auto& unitState = ask::get<entity::Unit>(emitting.updated, id);

            emitting.reporting.system->event(emitting.reporting.currentTurn, sw::io::UnitSpawned{
                .unitId = id,
                .unitType = "hunter",
                .x = unitState.position.x,
                .y = unitState.position.y,
            });
        }
    }
}
