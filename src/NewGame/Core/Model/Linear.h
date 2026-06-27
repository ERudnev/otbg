#pragma once

#include <unordered_map>
#include "NewGame/Core/Meta/TypeId.h"
#include "NewGame/Core/Model/Elementary.h"

namespace swexp::core::model::linear
{
    // naming this as "Id" looks fine, but leads to many "whoops" when missing with elementary::Id
    using TypeId = core::meta::Rttid;

    // required to put into erased complex container as one of "lines"
    struct Erased {
        virtual ~Erased();
    };

    // TODO: use concepts here
    template<typename Meta>
    struct State : Erased {
        using ElementId = typename elementary::Id<Meta>;
        using ElementState = typename elementary::State<Meta>;

        std::unordered_map<ElementId, ElementState> elements;
    };
}