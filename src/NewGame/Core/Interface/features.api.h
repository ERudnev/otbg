#pragma once

#include "NewGame/Core/Meta/Categories.h"
#include "NewGame/Core/Operations/_forwards.h"
#include "NewGame/Core/Model/_forwards.h"

// Gather core types to expose against Game features code
namespace swexp::core::api {

    // World-wide types:
    using Schema = swexp::core::model::Schema;

    // Feature categories:
    template<typename Meta>
    using Entity = ::swexp::core::cetegory::Entity<Meta>;

    template<typename Meta, typename Parent>
    using Extension = ::swexp::core::cetegory::Extension<Meta, Parent>;

    template<typename Meta, typename Parent>
    using Effect = ::swexp::core::cetegory::Effect<Meta, Parent>;

    template<typename Meta, typename AnchorEntity>
    using Composition = ::swexp::core::cetegory::Composition<Meta, AnchorEntity>;
}