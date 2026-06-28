#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Game/Entities/Unit.h"

#include <optional>

namespace swexp::game::effect
{
    using namespace swexp::core::api;

    struct OrderedToMove : Effect<OrderedToMove, entity::Unit> {
        struct State {
            entity::Map::Position targetPosition;
        };

        struct Actions final : BaseActions {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
