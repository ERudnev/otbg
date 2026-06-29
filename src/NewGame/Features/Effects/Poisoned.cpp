#include "NewGame/Features/Effects/Poisoned.h"

#include <algorithm>

#include "IO/interface.include.h"
#include "NewGame/Core/Manipulation/Helpers.h"
#include "NewGame/Features/Effects/Rended.h"

namespace swexp::game::effect
{
    namespace ask = ::swexp::core::manipulation;

    size_t Poisoned::Actions::updateEffect(Writing writing)
    {
        size_t updatedEffects = 0;
        auto& poisoned = writing.state.line<Poisoned>().elements;

        for (auto it = poisoned.begin(); it != poisoned.end();)
        {
            if (it->second.remainingTurns > 0)
            {
                --it->second.remainingTurns;
                ++updatedEffects;
            }

            if (it->second.remainingTurns == 0)
            {
                it = poisoned.erase(it);
            }
            else
            {
                ++it;
            }
        }

        return updatedEffects;
    }

    size_t Poisoned::Actions::applyEffect(Writing writing)
    {
        size_t appliedEffects = 0;
        auto& poisoned = writing.state.line<Poisoned>().elements;
        const auto& rended = writing.state.line<Rended>().elements;

        for (auto it = poisoned.begin(); it != poisoned.end();)
        {
            auto target = ask::try_get<entity::Unit>(writing, it->first);
            if (not target)
            {
                it = poisoned.erase(it);
                continue;
            }

            auto& effect = it->second;
            if (effect.remainingTurns == 0 or effect.damageBudgetRemaining == 0)
            {
                it = poisoned.erase(it);
                continue;
            }

            Damage damage = static_cast<Damage>(
                    (effect.damageBudgetRemaining + effect.remainingTurns - 1) / effect.remainingTurns);

            if (rended.contains(it->first))
            {
                damage = static_cast<Damage>(damage * 2);
            }

            damage = std::min(damage, effect.damageBudgetRemaining);
            if (damage == 0)
            {
                ++it;
                continue;
            }

            effect.damageBudgetRemaining -= damage;
            target->hitPoints
                    = target->hitPoints > damage ? static_cast<entity::Unit::HitPoints>(target->hitPoints - damage) : 0;

            writing.reporting.system->event(
                    writing.reporting.currentTurn,
                    sw::io::UnitAttacked{
                            .attackerUnitId = effect.applier,
                            .targetUnitId = it->first,
                            .damage = damage,
                            .targetHp = target->hitPoints,
                    });
            ++appliedEffects;

            if (target->hitPoints == 0)
            {
                writing.reporting.system->event(
                        writing.reporting.currentTurn,
                        sw::io::UnitDied{
                                .unitId = it->first,
                        });
                writing.state.line<entity::Unit>().elements.erase(it->first);
                it = poisoned.erase(it);
                continue;
            }

            if (effect.damageBudgetRemaining == 0)
            {
                it = poisoned.erase(it);
                continue;
            }

            ++it;
        }

        return appliedEffects;
    }
}
