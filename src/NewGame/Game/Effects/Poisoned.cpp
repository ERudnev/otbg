#include "NewGame/Game/Effects/Poisoned.h"

namespace swexp::game::effect
{
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
                it = poisoned.erase(it);
            else
                ++it;
        }

        return updatedEffects;
    }
}
