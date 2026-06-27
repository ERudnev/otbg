#pragma once

#include <unordered_map>
#include "NewGame/Core/References.h"
#include "NewGame/Core/Meta/TypeId.h"
#include "NewGame/Core/Model/Linear.h"

namespace swexp::core::model::intertype
{
    // naming this as "Id" looks fine, but leads to many "whoops" when missing with elementary::Id
    using TypeId = core::model::linear::TypeId;

    struct Composition {
        // NB: vector<pair<>> works faster here...
        std::unordered_map<TypeId, ref<core::model::linear::Erased>> lines;
    };

    struct SchemaData {
        struct TypeInfo {
        };

        std::unordered_map<TypeId, TypeInfo> types;

        // helper:
        template<typename ...Types> // variadic
        static cref<SchemaData> build();
    };
}

namespace swexp::core::model::intertype
{

}