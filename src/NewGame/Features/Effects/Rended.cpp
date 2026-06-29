#include "NewGame/Features/Effects/Rended.h"

namespace swexp::game::effect
{
    size_t Rended::Actions::updateEffect(Writing writing)
    {
        size_t updatedEffects = 0;
        auto& rended = writing.state.line<Rended>().elements;

        for (auto it = rended.begin(); it != rended.end();)
        {
            if (it->second.remainingTurns > 0)
            {
                --it->second.remainingTurns;
                ++updatedEffects;
            }

            if (it->second.remainingTurns == 0)
                it = rended.erase(it);
            else
                ++it;
        }

        return updatedEffects;
    }
}
