#pragma once

#include <cstdint> // TODO: remove after Identifier<Meta> used
#include "NewGame/Core/Logic/_forwards.h"

// temp:
#include "NewGame/Core/Meta/Alias.h"
#include "NewGame/Core/Logic/ContextData.h"
#include "NewGame/Core/Model/Complex.h"


namespace swexp::core::cetegory
{
    // This is collapsed "State/Operations/Normalizators/Commands/Emitters" Meta-class
    // See documentation for details
    template<typename Meta>
    class Entity {
    public:
        // TODO: disable default c-tor for this one.
        // TODO: use non-alias type generator like EnTT Identifier<Meta>
        using Id = uint32_t;

        struct BaseLogic {
            // injecting to operations signatures to allow
            // "Foo::Logic::getValue(Reading, Id)->Foo::Property"
            using Reading = ::swexp::core::operations::ReadingContext;
            using Writing = ::swexp::core::operations::WritingContext;

        protected:
            static const meta::Item<Meta>& Get(Reading context, Id id) { return context.state.line<Meta>().elements.at(id); }
            static meta::Item<Meta>& Get(Writing context, Id id) { return context.state.line<Meta>().elements.at(id); }
        };

        struct BaseEmitters {
            // TODO: rename
            using Analysis = ::swexp::core::operations::AnalyticContext;
        };
    };

    template<typename Meta, typename Parent>
    class Extension : protected Entity<Meta> {
    public:
        using Id = typename Parent::Id;

        struct BaseLogic : Parent::BaseLogic {
        };

        struct BaseEmitters : Parent::BaseEmitters {
        };
    };

    // TODO: adding BaseLogic rules and make Effect not similar to Extension
    template<typename Meta, typename Parent>
    class Effect : protected Entity<Meta> {
    public:
        using Id = typename Parent::Id;

        struct BaseLogic : Parent::BaseLogic {
        };

        struct BaseEmitters : Parent::BaseEmitters {
        };
    };


}