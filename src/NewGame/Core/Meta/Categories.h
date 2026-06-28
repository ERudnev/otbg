#pragma once

#include <cstdint> // TODO: remove after Identifier<Meta> used

namespace swexp::core::cetegory
{
    // This is collapsed "State/Operations/Normalizators/Commands/Emitters" Meta-class
    // See documentation for details
    template<typename Meta>
    class Entity {
    public:
        using Id = uint32_t; // use non-alias later: Identifier<Meta>;

        struct BaseLogic {
        };

        struct BaseEmitters {
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