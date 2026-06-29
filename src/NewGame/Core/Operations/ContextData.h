#pragma once

#include "NewGame/Core/Model/_forwards.h"
#include "NewGame/Core/ReportingContext.h"

namespace swexp::core::operations
{
    // This objects are intended to be copied through stack in user function calls like:
    // Foo::Actons::MakeSomething(Context where, Value howMuch);
    struct ContextReadingData {
        const model::complex::State& state;
        const ReportingContext reporting;
    };

    // This is basic implementation. Switch to StateView{const State&, Patch&} ECS-style
    struct ContextWritingData {
        model::complex::State& state;
        const ReportingContext reporting;

        operator ContextReadingData() const { return {state, reporting}; }
    };

    struct ContextReactionsData {
        const ContextReadingData initial;
        const ContextWritingData updated;
        model::complex::State& adjustments;
        const ReportingContext reporting;

        operator ContextReadingData() const { return {updated.state, reporting}; }
        operator ContextWritingData() { return {adjustments, reporting}; }
    };

    struct ContextEmittersData {
        const ContextReadingData initial;
        const ContextReadingData updated;
        const ReportingContext reporting;

        operator ContextReadingData() const { return {updated.state, reporting}; }
    };
}
