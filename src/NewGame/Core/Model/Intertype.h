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
        using Lines = std::unordered_map<TypeId, ref<core::model::linear::Erased>>;

        Composition(Schema schema) : schema(schema) {}

        const model::Schema schema;
        Lines lines;
    };

    struct SchemaData {
        struct TypeInfo {
            // TODO: if you need type dependency graph, put your data here..
            // like "std::vector<TypeId> requiredTypes"

            // add type-restored bindings here:
        };

        std::unordered_map<TypeId, TypeInfo> types;

        // syntax sugar:
        template<typename ...Types> // variadic
        static cref<SchemaData> build();
    };
}

namespace swexp::core::model::intertype
{
    template<typename ...Types> // variadic
    cref<SchemaData> SchemaData::build()
    {
        _INCOMPLETE_;
    }

}