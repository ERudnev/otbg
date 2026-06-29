#pragma once

#include <cstddef>

#include "IO/System/EventSystem.hpp"
#include "NewGame/Core/Model/_forwards.h"

// TODO: move to separate layer? Manipulation->InternalStateAlgorithm :)
namespace swexp::core::mechanism
{
    struct StateProcessing {
        using State = model::complex::State;

        struct TrivialStats {
            size_t eventsOccur = 0;
        };

        // TODO: add failed journal, logging channel and other mature stuff
        using NormalizationSummary = TrivialStats;
        // Just stats for debug? No other use is visible atm.
        using EmittersSummary = NormalizationSummary;

        static NormalizationSummary normalize(const State& initial, State& draft);
        static EmittersSummary emitEvents(const State& begin, const State& end, sw::EventSystem&);
    };
}