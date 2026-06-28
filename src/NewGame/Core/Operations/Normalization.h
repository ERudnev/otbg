#pragma once

#include <cstddef>

#include "NewGame/Core/Model/_forwards.h"

namespace swexp::core::operations
{
    struct Normalizer {
        struct Result {
            // placeholder:
            size_t elementsUpdated = 0;
            // TODO: add failed journal, logging channel and other mature stuff
        };

        static Result normalize(model::complex::State&);
    };
}