#pragma once

#include <memory>

// TODO: remove this include on project release
#include "NewGame/Core/Interface/macros.h"

namespace swexp::core
{
    // NOTE: this using is made for futore replacement with non-nullable "shared_reference"
    // this may keep many-many obvious "if's" away from the code.
    template <typename T>
    using ref = std::shared_ptr<T>;

    template <typename T>
    using cref = std::shared_ptr<const T>;
}
