#pragma once

#include <optional>

namespace swexp::core::model::elementary
{
    // use concept here
    template <typename Meta>
    using Id = typename Meta::Id;

    template <typename Meta>
    using State = typename Meta::State;

    // Classes below are planned direction of evolution of sw experiment
    template <typename Meta>
    using Patch = std::optional<typename Meta::State>;

    template <typename Meta>
    struct Update {
        std::optional<State<Meta>> initial; // nullopt if object is newly created
        Patch<Meta> patch;

        bool isNoop() const { return not initial and not patch; }
        bool isAdded() const { return not noop() and not initial; }
    };
}
