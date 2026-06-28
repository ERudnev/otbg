#pragma once

#include "NewGame/Core/Interface/features.api.h"
#include "NewGame/Features/Map.h"

#include <optional>

namespace swexp::game::entity
{
    using namespace swexp::core::api;

    struct Movement : Entity<Movement> {
        struct State {
            std::optional<Map::Position> targetPosition;
            uint32_t stepDistance{1};
        };

        struct Logic final : BaseLogic {
        };

        struct Emitters final : BaseEmitters {
        };
    };
}
