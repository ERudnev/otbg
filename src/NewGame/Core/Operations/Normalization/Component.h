#pragma once

#include "NewGame/Core/Model/Complex.h"

namespace swexp::core::normalization
{
    template<typename ComponentType, typename ParentType>
    void checkComponentAttachment(model::complex::State&);
}

// Impl
namespace swexp::core::normalization
{
    template<typename ComponentType, typename ParentType>
    void checkComponentAttachment(model::complex::State& state)
    {
        auto& components = state.line<ComponentType>().elements;
        const auto& parents = state.line<ParentType>().elements;

        for (auto it = components.begin(); it != components.end();)
        {
            if (!parents.contains(it->first))
                it = components.erase(it);
            else
                ++it;
        }
    }
}