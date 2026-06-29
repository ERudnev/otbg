#pragma once

#include <string>
#include <typeindex>
#include <typeinfo>

namespace swexp::core::meta
{
    // NB: serialize this will cause trouble.
    using Rttid = std::type_index;

    // TODO: replace this with persistent type Id's / names.
    using StaticTypeId = std::string;
    // Current implementation is runtime/compiler-dependent,
    // but still better than passing borrowed const char* around.
    template <typename Meta>
    const StaticTypeId& debugName()
    {
        static const StaticTypeId singleton = typeid(Meta).name();
        return singleton;
    }
}
