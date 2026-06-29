#pragma once

#include "IO/System/EventSystem.hpp"

namespace swexp::core
{
    struct ReportingContext {
        uint32_t currentTurn{};
        sw::EventSystem* system{};
    };
}
