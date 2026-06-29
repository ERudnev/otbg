#pragma once

#include "NewGame/Core/Mechanism/Helpers.h"
#include "NewGame/Core/Operations/ContextData.h"
#include "NewGame/Core/Model/Complex.h"

namespace swexp::core::normalization
{
    template<typename ComponentType, typename ParentType>
    size_t deleteWithParent(core::api::context::Reacting reacting);
}

// Impl
namespace swexp::core::normalization
{
    template<typename ComponentType, typename ParentType>
    size_t deleteWithParent(core::api::context::Reacting reacting)
    {
        const auto& initial = reacting.initial.state;
        const auto& updated = reacting.updated.state;
        auto& adjustments = reacting.adjustments;

        size_t result = 0;
        for (const auto parentId : mechanism::helpers::findDeleted<ParentType>(initial, updated))
            result += adjustments.line<ComponentType>().elements.erase(parentId);

        return result;
    }
}
