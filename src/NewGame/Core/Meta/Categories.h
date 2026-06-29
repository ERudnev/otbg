#pragma once

#include <cstdint> // TODO: remove after Identifier<Meta> used
#include <cstddef>
#include <functional>
#include "NewGame/Core/Operations/_forwards.h"

// temp:
#include "NewGame/Core/Meta/Alias.h"
#include "NewGame/Core/Operations/ContextData.h"
#include "NewGame/Core/Operations/Normalization/Component.h"
#include "NewGame/Core/Model/Complex.h"


namespace swexp::core::cetegory
{
    // This is collapsed "State/Operations/Normalizators/Commands/Emitters" Meta-class
    // See documentation for details
    template<typename Meta>
    struct Entity {
        // TODO: disable default c-tor for this one.
        // TODO: use non-alias type generator like EnTT Identifier<Meta>
        using Id = uint32_t;

        struct BaseActions {
            // injecting to operations signatures to allow
            // "Foo::Logic::getValue(Reading, Id)->Foo::Property"
            using Reading = api::context::Reading;
            using Writing = api::context::Writing;

        protected:
            static const meta::Item<Meta>& Get(Reading context, Id id) { return context.state.line<Meta>().elements.at(id); }
            static meta::Item<Meta>& Get(Writing context, Id id) { return context.state.line<Meta>().elements.at(id); }
        };

        struct BaseReactions {
            using Reacting = api::context::Reacting;
            using Summary = size_t;
        };

        struct BaseEmitters {
            using Emitting = api::context::Emitting;
            using CallAllFunction = std::function<void(Emitting)>;
        };
    };

    template<typename Meta, typename Parent>
    struct Extension : protected Entity<Meta> {
        using Id = typename Parent::Id;

        struct BaseActions : Entity<Meta>::BaseActions {
        };

        struct BaseReactions : Entity<Meta>::BaseReactions {
            using Reacting = typename Entity<Meta>::BaseReactions::Reacting;
            using Summary = typename Entity<Meta>::BaseReactions::Summary;
        protected:
            static Summary _category_default_reactions(Reacting context)
            {
                return normalization::deleteWithParent<Meta, Parent>(context);
            }
        };

        struct BaseEmitters : Entity<Meta>::BaseEmitters {
        };
    };

    // TODO: adding BaseActions rules and make Effect not similar to Extension
    template<typename Meta, typename Parent>
    struct Effect : protected Entity<Meta> {
        using Id = typename Parent::Id;

        struct BaseActions : Entity<Meta>::BaseActions {
        };

        struct BaseReactions : Entity<Meta>::BaseReactions {
            using Reacting = typename Entity<Meta>::BaseReactions::Reacting;
            using Summary = typename Entity<Meta>::BaseReactions::Summary;
        protected:
            static Summary _category_default_reactions(Reacting context)
            {
                return normalization::deleteWithParent<Meta, Parent>(context);
            }
        };

        struct BaseEmitters : Entity<Meta>::BaseEmitters {
        };
    };

    // TODO: create Composition rules for this Category
    template<typename Meta, typename AnchorEntity>
    using Composition = Extension<Meta, AnchorEntity>;


}