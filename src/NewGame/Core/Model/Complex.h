#pragma once

#include "NewGame/Core/Model/_forwards.h"
#include "NewGame/Core/Model/Linear.h"
#include "NewGame/Core/Model/Intertype.h"

#include <typeinfo>

namespace swexp::core::model::complex
{
    struct State : protected intertype::Composition {
        State(Schema schema);
        State(const State& other);

        // TODO: repace this with "applyPatch" for much better performance
        void applyFrom(const State& other);

        Schema getSchema() const { return schema; }

        template<typename Meta>
        const linear::State<Meta>& line() const;

        template<typename Meta>
        linear::State<Meta>& line();
    private:
        void fillZeroState();
    };
}

// Impl:
namespace swexp::core::model::complex
{
    template<typename Meta>
    const linear::State<Meta>& State::line() const
    {
        const auto iterator = lines.find(typeid(Meta));
        if (iterator == lines.end())
        {
            throw std::bad_cast();
        }

        const auto* typed = dynamic_cast<const linear::State<Meta>*>(iterator->second.get());
        if (typed == nullptr)
        {
            throw std::bad_cast();
        }

        return *typed;
    }

    template<typename Meta>
    linear::State<Meta>& State::line()
    {
        const auto iterator = lines.find(typeid(Meta));
        if (iterator == lines.end())
        {
            throw std::bad_cast();
        }

        auto* typed = dynamic_cast<linear::State<Meta>*>(iterator->second.get());
        if (typed == nullptr)
        {
            throw std::bad_cast();
        }

        return *typed;
    }
}
