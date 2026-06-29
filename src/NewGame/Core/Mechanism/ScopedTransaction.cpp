#include "NewGame/Core/Mechanism/ScopedTransaction.h"

#include "NewGame/Core/Mechanism/StateProcessing.h"

#include <stdexcept>

namespace swexp::core::mechanism
{
    // this code runs in desctructor, so, very fragile for exceptions
    // TODO: implement as external explicit operation
    void ScopedTransaction::finish()
    {
        // WARNING, this is initial implementation
        // and it is very, very, very slow
        // all container copies here must be replaced with State reference/Patch mechanism
        const State initial(state);

        State was(initial);
        State want(collected);

        constexpr size_t maxNormalizationCycles = 10;
        for (size_t cycle = 0; cycle < maxNormalizationCycles; ++cycle)
        {
            State better(want);
            const auto improvements = StateProcessing::normalize(was, want, better);

            if (improvements == 0)
            {
                StateProcessing::emitEvents(initial, want, receiver);
                state.applyFrom(want);
                return;
            }

            was.applyFrom(want);
            want.applyFrom(better);
        }

        throw std::logic_error("ScopedTransaction::finish: normalization did not converge");
    }
}