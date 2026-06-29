#include "NewGame/Core/Mechanism/StateProcessing.h"

#include "NewGame/Core/Interface/macros.h"
#include "NewGame/Core/Model/Complex.h"

namespace swexp::core::mechanism
{
    StateProcessing::NormalizationSummary StateProcessing::normalize(
            const StateProcessing::State& initial,
            const StateProcessing::State& updated,
            StateProcessing::State& reactions,
            core::ReportingContext reporting)
    {
        NormalizationSummary result = 0;

        const auto schema = updated.getSchema();
        for (const auto& [_, type] : schema->types)
        {
            if (!type.callReactions)
            {
                continue;
            }

            result += type.callReactions(initial, updated, reactions, reporting);
        }

        return result;
    }

    StateProcessing::EmittersSummary StateProcessing::emitEvents(
            const StateProcessing::State& begin, const StateProcessing::State& end, core::ReportingContext reporting)
    {
        EmittersSummary result = 0;

        const auto schema = end.getSchema();
        for (const auto& [_, type] : schema->types)
        {
            if (!type.callEmitters)
            {
                continue;
            }

            type.callEmitters(begin, end, reporting);
            ++result;
        }

        return result;
    }
}
