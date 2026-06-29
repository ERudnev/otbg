#include "NewGame/Features/Abilities/PoisonArrows.h"

#include "IO/interface.include.h"
#include "NewGame/Core/Interface/InjectedRandomDevice.h"

namespace swexp::game::ability
{
    bool PoisonArrows::Actions::tryApply(Writing writing, Id applierId, entity::Unit::Id targetId)
    {
        const auto& poisonArrows = Get(writing, applierId);
        if (core::interface::InjectedRandomDevice::next() >= poisonArrows.chance)
            return false;

        writing.state.line<effect::Poisoned>().createOrUpdateComponent<entity::Unit>(
            targetId,
            effect::Poisoned::State{
                .applier = applierId,
                .damageBudgetRemaining = poisonArrows.damage,
                .remainingTurns = poisonArrows.duration,
            });

        writing.reporting.system->event(writing.reporting.currentTurn, sw::io::UnitAbilityUsed{
            .abilityUnitId = applierId,
            .abilityName = "poison_arrows",
        });

        return true;
    }
}
