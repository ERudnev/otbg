#include "NewGame/Core/Mechanism/StateProcessing.h"

#include "NewGame/Core/Interface/macros.h"
#include "NewGame/Core/Model/Complex.h"

namespace swexp::core::mechanism
{
    StateProcessing::NormalizationSummary StateProcessing::normalize(const State& in, State& out)
    {
        _INCOMPLETE_;
    }

    StateProcessing::EmittersSummary StateProcessing::emitEvents(
        const State& begin, const State& end, sw::EventSystem& listener)
    {
        EmittersSummary result;

        const auto schema = end.getSchema();
        for (const auto& [_, type] : schema->types)
        {
            if (!type.callEmitters)
                continue;

            type.callEmitters(begin, end, listener);
            ++result.eventsOccur;
        }

        return result;
    }
}
