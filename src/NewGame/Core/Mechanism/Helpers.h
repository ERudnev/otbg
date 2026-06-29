#pragma once

#include <vector>

#include "NewGame/Core/Model/Complex.h"

namespace swexp::core::mechanism::helpers
{
    using State = model::complex::State;

    template<typename Meta>
    using Ids = std::vector<typename Meta::Id>;

    template<typename Meta>
    Ids<Meta> findAdded(const State& initial, const State& updated);

    template<typename Meta>
    Ids<Meta> findAddedOrUpdated(const State& initial, const State& updated);

    template<typename Meta>
    Ids<Meta> findDeleted(const State& initial, const State& updated);
}


// Impl
namespace swexp::core::mechanism::helpers
{
    template<typename Meta>
    Ids<Meta> findAdded(const State& initial, const State& updated)
    {
        const auto& before = initial.line<Meta>().elements;
        const auto& after = updated.line<Meta>().elements;

        Ids<Meta> result;
        result.reserve(after.size());

        for (const auto& [id, _] : after)
        {
            if (before.find(id) == before.end())
                result.push_back(id);
        }

        return result;
    }

    template<typename Meta>
    Ids<Meta> findAddedOrUpdated(const State& initial, const State& updated)
    {
        const auto& before = initial.line<Meta>().elements;
        const auto& after = updated.line<Meta>().elements;

        Ids<Meta> result;
        result.reserve(after.size());

        for (const auto& [id, itemState] : after)
        {
            const auto previous = before.find(id);
            if (previous == before.end() || previous->second != itemState)
                result.push_back(id);
        }

        return result;
    }

    template<typename Meta>
    Ids<Meta> findDeleted(const State& initial, const State& updated)
    {
        const auto& before = initial.line<Meta>().elements;
        const auto& after = updated.line<Meta>().elements;

        Ids<Meta> result;
        result.reserve(before.size());

        for (const auto& [id, _] : before)
        {
            if (after.find(id) == after.end())
                result.push_back(id);
        }

        return result;
    }
}
