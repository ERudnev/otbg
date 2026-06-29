#pragma once

#include "NewGame/Core/Model/_forwards.h"

#include <functional>
#include <string>
#include <type_traits>
#include <unordered_map>
#include "NewGame/Core/References.h"
#include "NewGame/Core/Meta/TypeId.h"
#include "NewGame/Core/Model/Linear.h"
#include "NewGame/Core/Operations/ContextData.h"

namespace sw
{
    class EventSystem;
}

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

            meta::StaticTypeId debugName;
            std::function<ref<core::model::linear::Erased>()> makeZeroLine;
            std::function<ref<core::model::linear::Erased>(const core::model::linear::Erased&)> cloneLine;
            std::function<void(const core::model::complex::State&, const core::model::complex::State&, sw::EventSystem&)> callEmitters;
        };

        std::unordered_map<TypeId, TypeInfo> types;

        // syntax sugar:
        template<typename ...Types> // variadic
        static cref<SchemaData> build();
    };
}

namespace swexp::core::model::intertype
{
    namespace detail
    {
        template<typename Meta, typename = void>
        struct has_generated_call_all : std::false_type {};

        template<typename Meta>
        struct has_generated_call_all<
            Meta,
            std::void_t<decltype(&Meta::Emitters::_generated_call_all)>>
            : std::true_type {};

        template<typename Meta>
        inline constexpr bool has_generated_call_all_v = has_generated_call_all<Meta>::value;

        using CallEmittersFn = std::function<void(
            const core::model::complex::State&,
            const core::model::complex::State&,
            sw::EventSystem&)>;

        template<typename Meta>
        CallEmittersFn makeCallEmitters()
        {
            if constexpr (has_generated_call_all_v<Meta>)
            {
                return [](
                    const core::model::complex::State& begin,
                    const core::model::complex::State& end,
                    sw::EventSystem& listener)
                {
                    Meta::Emitters::_generated_call_all(core::operations::ContextEmittersData{
                        core::operations::ContextReadingData{begin},
                        core::operations::ContextReadingData{end},
                        listener,
                    });
                };
            }
            else
            {
                return {};
            }
        }
    }

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
                    .debugName = core::meta::debugName<Types>(),
                    .makeZeroLine = &makeZeroLine<Types>,
                    .cloneLine = &cloneLine<Types>,
                    .callEmitters = detail::makeCallEmitters<Types>(),
                }),
            ...);

        return schema;
    }

}