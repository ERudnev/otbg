#pragma once

#include <cstddef>

#include "IO/System/EventSystem.hpp"
#include "NewGame/Core/Model/_forwards.h"

// TODO: move to separate layer? Manipulation->InternalStateAlgorithm :)
namespace swexp::core::mechanism
{
    struct StateProcessing {
        using State = model::complex::State;

        using TrivialStats = size_t;

        // TODO: add failed journal, logging channel and other mature stuff
        using NormalizationSummary = TrivialStats;
        // Just stats for debug? No other use is visible atm.
        using EmittersSummary = NormalizationSummary;

        static NormalizationSummary normalize(const State& initial, const State& updated, State& reactions);
        static EmittersSummary emitEvents(const State& begin, const State& end, sw::EventSystem&);
    };
}