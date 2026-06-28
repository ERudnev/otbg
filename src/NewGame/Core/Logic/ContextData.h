#pragma once

#include "NewGame/Core/Model/_forwards.h"

namespace swexp::core::operations
{
    // this is placeholder for Operational semantics
    struct ContextData {
        model::complex::State& state;
    };

    struct ContextUpdatesData {
        const model::complex::State& current;
        model::complex::State& planned;
    };
}