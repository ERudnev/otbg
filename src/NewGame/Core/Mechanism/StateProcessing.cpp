#include "NewGame/Core/Mechanism/StateProcessing.h"

#include "NewGame/Core/Interface/macros.h"
#include "NewGame/Core/Model/Complex.h"

namespace swexp::core::mechanism
{
    StateProcessing::NormalizationSummary StateProcessing::normalize(
        const StateProcessing::State& initial,
        const StateProcessing::State& updated,
        StateProcessing::State& reactions)
    {
        NormalizationSummary result = 0;

        const auto schema = updated.getSchema();
        for (const auto& [_, type] : schema->types)
        {
            if (!type.callReactions)
                continue;

            result += type.callReactions(initial, updated, reactions);
        }

        return result;
    }

    StateProcessing::EmittersSummary StateProcessing::emitEvents(
        const StateProcessing::State& begin,
        const StateProcessing::State& end,
        sw::EventSystem& listener)
    {
        EmittersSummary result = 0;

        const auto schema = end.getSchema();
        for (const auto& [_, type] : schema->types)
        {
            if (!type.callEmitters)
                continue;

            type.callEmitters(begin, end, listener);
            ++result;
        }

        return result;
    }
}
