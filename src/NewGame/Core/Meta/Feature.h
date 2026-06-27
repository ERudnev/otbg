#pragma once

#include <cstdint> // TODO: remove

namespace swexp::core::meta
{
    template<typename Meta>
    class Feature {
    public:
        using Id = uint32_t; // use non-alias later: Identifier<Meta>;

    protected:
        struct BaseOperations {
        };

        struct BaseRules {
        };

        struct BaseEmitters {
        };
    };
}