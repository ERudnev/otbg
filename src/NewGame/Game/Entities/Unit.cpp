#include "NewGame/Game/Entities/Unit.h"

#include "NewGame/Core/Manipulation/Helpers.h"

namespace swexp::game::entity
{
    namespace ask = ::swexp::core::manipulation;

    bool Unit::Actions::makeTurn(Writing writing, Id id)
    {
        auto unit = ask::try_get<Unit>(writing, id);
        if (not unit)
            return false;

        if (unit->hitPoints == 0)
            return false;

        if (not unit->turnStrategy)
            return false;

        return unit->turnStrategy(writing, id);
    }
}
