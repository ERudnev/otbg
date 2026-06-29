#include "NewGame/Features/Abilities/RangedAttack.h"

#include "IO/interface.include.h"
#include "NewGame/Core/Manipulation/Helpers.h"

namespace swexp::game::ability
{
    namespace ask = ::swexp::core::manipulation;

    void RangedAttack::Actions::attack(Writing writing, Id attackerId, entity::Unit::Id targetId)
    {
        const auto damage = Get(writing, attackerId).damage;
        auto& target = ask::get<entity::Unit>(writing, targetId);

        target.hitPoints
                = target.hitPoints > damage ? static_cast<entity::Unit::HitPoints>(target.hitPoints - damage) : 0;

        writing.reporting.system->event(
                writing.reporting.currentTurn,
                sw::io::UnitAttacked{
                        .attackerUnitId = attackerId,
                        .targetUnitId = targetId,
                        .damage = damage,
                        .targetHp = target.hitPoints,
                });
    }
}
