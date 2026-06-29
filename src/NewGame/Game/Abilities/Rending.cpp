#include "NewGame/Game/Abilities/Rending.h"

#include "IO/interface.include.h"
#include "NewGame/Core/Interface/InjectedRandomDevice.h"
#include "NewGame/Core/Manipulation/Helpers.h"
#include "NewGame/Game/Effects/Rended.h"

namespace swexp::game::ability
{
    namespace ask = ::swexp::core::manipulation;

    bool Rending::Actions::tryApply(Writing writing, Id applierId, entity::Unit::Id targetId)
    {
        const auto& rending = Get(writing, applierId);
        if (core::interface::InjectedRandomDevice::next() >= rending.chance)
            return false;

        auto& target = ask::get<entity::Unit>(writing, targetId);
        target.hitPoints = target.hitPoints > rending.damage
            ? static_cast<entity::Unit::HitPoints>(target.hitPoints - rending.damage)
            : 0;

        writing.state.line<effect::Rended>().createOrUpdateComponent<entity::Unit>(
            targetId,
            effect::Rended::State{
                .applier = applierId,
                .damage = rending.damage,
                .remainingTurns = 1,
            });

        writing.reporting.system->event(writing.reporting.currentTurn, sw::io::UnitAbilityUsed{
            .abilityUnitId = applierId,
            .abilityName = "rending",
        });
        return true;
    }
}
