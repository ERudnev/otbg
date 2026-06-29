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

            friend bool operator==(const State&, const State&) = default;
        };

        struct Actions final : BaseActions {
            static void order(Writing, entity::Unit::Id, entity::Map::Position target);
        };

        struct Reactions final : BaseReactions {
            static void _generated_call_all(Reacting);
            static void finishedMarchRemoved(Reacting);
        };

        struct Emitters final : BaseEmitters {
            static void _generated_call_all(Emitting);
            static void marchStarted(Emitting);
        };
    };
}
