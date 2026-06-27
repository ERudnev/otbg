#pragma once

#include <typeindex>

namespace swexp::core::meta
{
    // NB: serialize this will cause trouble.
    using Rttid = std::type_index;

    // TODO: add persistent type Id's as strings
}