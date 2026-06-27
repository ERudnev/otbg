#pragma once

#include "NewGame/Core/Meta/Feature.h"
#include "NewGame/Core/Operations/_forwards.h"

namespace swexp::core::api {

    template<typename Meta>
    using Feature = ::swexp::core::meta::Feature<Meta>;

    using Context = ::swexp::core::operations::Context;
}