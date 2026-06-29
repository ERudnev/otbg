#pragma once

#include "NewGame/Core/Model/_forwards.h"

#include <functional>
#include <string>
#include <unordered_map>
#include "NewGame/Core/References.h"
#include "NewGame/Core/Meta/TypeId.h"
#include "NewGame/Core/Model/Linear.h"
#include "NewGame/Core/Operations/ContextData.h"
#include "NewGame/Core/ReportingContext.h"

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

        Composition(Schema schema)
            : schema(schema)
        {
        }

        const model::Schema schema;
        Lines lines;
    };

    struct SchemaData {
        struct TypeInfo {
            using ComplexState = core::model::complex::State;
            // TODO: if you need type dependency graph, put your data here..
            // like "std::vector<TypeId> requiredTypes"

            meta::StaticTypeId debugName;
            std::function<ref<core::model::linear::Erased>()> makeZeroLine;
            std::function<ref<core::model::linear::Erased>(const core::model::linear::Erased&)> cloneLine;
            std::function<void(const ComplexState&, const ComplexState&, core::ReportingContext)> callEmitters;
            std::function<size_t(const ComplexState&, const ComplexState&, ComplexState&, core::ReportingContext)>
                    callReactions;
        };

        std::unordered_map<TypeId, TypeInfo> types;

        // syntax sugar:
        template <typename... Types> // variadic
        static cref<SchemaData> build();
    };
}

namespace swexp::core::model::intertype
{
    template <typename Meta>
    auto makeCallReactions()
    {
        using CallReactionsFn = std::function<size_t(
                const core::model::complex::State&,
                const core::model::complex::State&,
                core::model::complex::State&,
                core::ReportingContext)>;

        return CallReactionsFn{
                [](const core::model::complex::State& initial,
                   const core::model::complex::State& updated,
                   core::model::complex::State& adjustments,
                   core::ReportingContext reporting)
                {
                    return Meta::Reactions::_generated_call_all(
                            core::operations::ContextReactionsData{
                                    core::operations::ContextReadingData{initial, reporting},
                                    core::operations::ContextWritingData{
                                            const_cast<core::model::complex::State&>(updated), reporting},
                                    adjustments,
                                    reporting,
                            });
                }};
    }

    template <typename Meta>
    auto makeCallEmitters()
    {
        using CallEmittersFn = std::function<void(
                const core::model::complex::State&, const core::model::complex::State&, core::ReportingContext)>;

        return CallEmittersFn{[](const core::model::complex::State& begin,
                                 const core::model::complex::State& end,
                                 core::ReportingContext reporting)
                              {
                                  Meta::Emitters::_generated_call_all(
                                          core::operations::ContextEmittersData{
                                                  core::operations::ContextReadingData{begin, reporting},
                                                  core::operations::ContextReadingData{end, reporting},
                                                  reporting,
                                          });
                              }};
    }

    template <typename Meta>
    ref<core::model::linear::Erased> makeZeroLine()
    {
        return std::make_shared<core::model::linear::State<Meta>>();
    }

    template <typename Meta>
    ref<core::model::linear::Erased> cloneLine(const core::model::linear::Erased& erased)
    {
        const auto& typed = dynamic_cast<const core::model::linear::State<Meta>&>(erased);
        return std::make_shared<core::model::linear::State<Meta>>(typed);
    }

    template <typename... Types> // variadic
    cref<SchemaData> SchemaData::build()
    {
        auto schema = std::make_shared<SchemaData>();

        (schema->types.emplace(
                 TypeId(typeid(Types)),
                 TypeInfo{
                         .debugName = core::meta::debugName<Types>(),
                         .makeZeroLine = &makeZeroLine<Types>,
                         .cloneLine = &cloneLine<Types>,
                         .callEmitters = makeCallEmitters<Types>(),
                         .callReactions = makeCallReactions<Types>(),
                 }),
         ...);

        return schema;
    }

}
