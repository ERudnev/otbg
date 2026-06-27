#pragma once

#include <unordered_map>
#include "NewGame/Core/References.h"
#include "NewGame/Core/Meta/TypeTraits.h"
#include "NewGame/Core/State/Linear/Erased.h"

namespace swexp::core::state::structure
{
    struct Composition {
        using TypeId = core::meta::Rttid;

        // NB: vector<pair<>> works faster here...
        std::unordered_map<TypeId, ref<core::state::linear::Erased>> lines;
    };
}