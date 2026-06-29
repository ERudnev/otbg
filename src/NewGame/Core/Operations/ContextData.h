#pragma once

#include "IO/System/EventSystem.hpp"
#include "NewGame/Core/Model/_forwards.h"

namespace swexp::core::operations
{
    // This objects are intended to be copied through stack in user function calls like:
    // Foo::Actons::MakeSomething(Context where, Value howMuch);
    struct ContextReadingData {
        const model::complex::State& state;
    };

    // This is basic implementation. Switch to StateView{const State&, Patch&} ECS-style
    struct ContextWritingData {
        model::complex::State& state;

        operator ContextReadingData() const { return {state}; }
    };

    struct ContextReactionsData {
        const ContextReadingData initial;
        const ContextWritingData updated;
        model::complex::State& adjustments;

        operator ContextReadingData() const { return {updated.state}; }
        operator ContextWritingData() { return {adjustments}; }
    };

    struct ContextEmittersData {
        const ContextReadingData initial;
        const ContextReadingData updated;
        sw::EventSystem& listener;

        operator ContextReadingData() const { return updated; }
    };
}