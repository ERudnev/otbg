#pragma once

#include "NewGame/Core/References.h"

// local forwards:
namespace swexp::core::model::intertype
{
    struct SchemaData;
}

// public alias:
namespace swexp::core::model
{
    using Schema = cref<::swexp::core::model::intertype::SchemaData>;
}

namespace swexp::core::model::complex
{
    struct State;
}