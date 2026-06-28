#pragma once

#include "NewGame/Core/Model/_forwards.h"

#include <functional>
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

            const char* debugName;
            std::function<ref<core::model::linear::Erased>()> makeZeroLine;
            std::function<ref<core::model::linear::Erased>(const core::model::linear::Erased&)> cloneLine;
        };

        std::unordered_map<TypeId, TypeInfo> types;

        // syntax sugar:
        template<typename ...Types> // variadic
        static cref<SchemaData> build();
    };
}

namespace swexp::core::model::intertype
{
    template<typename Meta>
    ref<core::model::linear::Erased> makeZeroLine()
    {
        return std::make_shared<core::model::linear::State<Meta>>();
    }

    template<typename Meta>
    ref<core::model::linear::Erased> cloneLine(const core::model::linear::Erased& erased)
    {
        const auto& typed = dynamic_cast<const core::model::linear::State<Meta>&>(erased);
        return std::make_shared<core::model::linear::State<Meta>>(typed);
    }

    template<typename ...Types> // variadic
    cref<SchemaData> SchemaData::build()
    {
        auto schema = std::make_shared<SchemaData>();

        (
            schema->types.emplace(
                TypeId(typeid(Types)),
                TypeInfo{
                    .debugName = typeid(Types).name(),
                    .makeZeroLine = &makeZeroLine<Types>,
                    .cloneLine = &cloneLine<Types>,
                }),
            ...);

        return schema;
    }

}