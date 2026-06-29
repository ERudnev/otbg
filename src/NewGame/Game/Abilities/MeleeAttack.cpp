#include "NewGame/Game/Abilities/MeleeAttack.h"

namespace swexp::game::ability
{
    namespace ask = ::swexp::core::manipulation;

    void MeleeAttack::Actions::attack(Writing writing, Id attackerId, entity::Unit::Id targetId)
    {
        const auto damage = Get(writing, attackerId).strength;
        auto& target = ask::get<entity::Unit>(writing, targetId);

        target.hitPoints = target.hitPoints > damage
            ? static_cast<entity::Unit::HitPoints>(target.hitPoints - damage)
            : 0;
    }
}
