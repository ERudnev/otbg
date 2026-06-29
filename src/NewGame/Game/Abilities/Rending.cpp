#include "NewGame/Game/Abilities/Rending.h"

#include "NewGame/Core/Interface/InjectedRandomDevice.h"
#include "NewGame/Core/Manipulation/Helpers.h"

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
        return true;
    }
}
