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
        (void)begin;
        (void)end;
        (void)listener;
        _INCOMPLETE_;
    }
}
