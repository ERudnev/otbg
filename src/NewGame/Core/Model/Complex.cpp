#include "NewGame/Core/Model/Complex.h"

namespace swexp::core::model::complex
{
    State::State(Schema schema)
        : intertype::Composition(schema)
    {
        fillZeroState();
    }

    State::State(const State& other)
        : intertype::Composition(other.schema)
    {
        for (const auto& [typeId, line] : other.lines)
        {
            const auto type = schema->types.find(typeId);
            if (type == schema->types.end())
            {
                throw std::bad_cast();
            }

            lines.emplace(typeId, type->second.cloneLine(*line));
        }
    }

    void State::applyFrom(const State& other)
    {
        if (schema != other.schema)
        {
            throw std::bad_cast();
        }

        for (const auto& [typeId, otherLine] : other.lines)
        {
            const auto type = schema->types.find(typeId);
            if (type == schema->types.end())
            {
                throw std::bad_cast();
            }

            lines[typeId] = type->second.cloneLine(*otherLine);
        }
    }

    void State::fillZeroState()
    {
        for (const auto& [typeId, type] : schema->types)
        {
            lines.emplace(typeId, type.makeZeroLine());
        }
    }
}
