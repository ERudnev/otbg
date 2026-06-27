#pragma once

#include <cstdint> // TODO: remove

namespace swexp::core::cetegory
{
    // This is collapsed "State/Operations/Normalizators/Commands/Emitters" Meta-class
    // See documentation for details
    template<typename Meta>
    class Entity {
    public:
        using Id = uint32_t; // use non-alias later: Identifier<Meta>;

    protected:
        struct BaseLogic {
        };

        struct BaseEmitters {
        };
    };

    template<typename Meta, typename Parent>
    class Extension : Entity<Meta> {
    public:
        using Id = typename Parent::Id;

    protected:
        struct BaseLogic : Parent::BaseLogic {
        };

        struct BaseEmitters : Parent::BaseEmitters {
        };
    };
}