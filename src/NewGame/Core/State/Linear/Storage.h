#pragma once

#include <unordered_map>

namespace swexp::core::state::linear
{
    // TODO: use concepts here
    template<typename Meta>
    struct Storage {
        using Id = typename Meta::Id;
        using Element = typename Meta::State;
        std::unordered_map<Id, Element> values;
    };
}