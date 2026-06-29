#pragma once

#include "IO/System/EventSystem.hpp"
#include "NewGame/Core/Operations/_forwards.h"
#include "NewGame/Core/Model/Complex.h"
#include "NewGame/Core/ReportingContext.h"

// Contexts spawned:
#include "NewGame/Core/Operations/ContextData.h"

namespace swexp::core::mechanism
{
    // Current implementation is straight-forward:
    // making deep copy of World. This can be avoided in the future (Patches or Immutability entangling, see docs for details)
    // Also it is a place for multi-threading (Transaction can share initial state with other threads and submit patches to the broker)
    // NB: to extend this, allow Transactions spawn lesser transactions and share context
    class ScopedTransaction {
    public:
        using State = ::swexp::core::model::complex::State;
        using Reading = api::context::Reading;
        using Writing = api::context::Writing;
        using Reacting = api::context::Reacting;
        using Emitting = api::context::Emitting;


        ScopedTransaction(State& target, core::ReportingContext reporting)
            : state(target), collected(target), reporting(reporting) {} // deep copy of target state
        ~ScopedTransaction() { finish(); }

        operator Reading() { return Reading{collected, reporting}; } // returning initial state allow independent operaions
        operator Writing() { return Writing{collected, reporting}; }

    private:
        State& state;
        State collected;
        core::ReportingContext reporting;
        // TODO: to make this public, implement invalidation and rollbacks (reset of collected)
        void finish();
    };
}