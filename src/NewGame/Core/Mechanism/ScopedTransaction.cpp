#include "NewGame/Core/Mechanism/ScopedTransaction.h"

#include "NewGame/Core/Mechanism/StateProcessing.h"

namespace swexp::core::mechanism
{
    // this code runs in desctructor, so, very fragile for exceptions
    // TODO: implement as external explicit operation
    void ScopedTransaction::finish()
    {
        // call all normalization for (state->collected)
        // scan changes for events (use Entity::Emitter lists)
        // emit found Enents
    }
}