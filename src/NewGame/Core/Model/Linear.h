#pragma once

#include <stdexcept>
#include <unordered_map>
#include "NewGame/Core/Meta/TypeId.h"
#include "NewGame/Core/Model/Elementary.h"

namespace swexp::core::model::linear
{
    // naming this as "Id" looks fine, but leads to many "whoops" when missing with elementary::Id
    using TypeId = core::meta::Rttid;

    // required to put into erased complex container as one of "lines"
    struct Erased {
        virtual ~Erased() = default;
    };

    // TODO: use concepts here
    template<typename Meta>
    struct State : Erased {
        using ElementId = typename elementary::Id<Meta>;
        using ElementState = typename elementary::State<Meta>;

        std::unordered_map<ElementId, ElementState> elements;

        // TODO: separate helpers as Core/Manipulation layer.. someday.
        ElementId createEntity(ElementState&&);

        template<typename ParentType>
        void createComponent(typename ParentType::Id, ElementState&&);

        template<typename ParentType>
        void createOrUpdateComponent(typename ParentType::Id, ElementState&&);

    private:
        ElementId createNewItem(ElementId, ElementState&&);
    };
}

namespace swexp::core::model::linear
{
    template<typename Meta>
    auto State<Meta>::createEntity(ElementState&& item) -> ElementId
    {
        const ElementId id = static_cast<ElementId>(elements.size());
        return createNewItem(id, std::move(item));
    }

    template<typename Meta>
    template<typename ParentType>
    void State<Meta>::createComponent(typename ParentType::Id parentId, ElementState&& item)
    {
        createNewItem(static_cast<ElementId>(parentId), std::move(item));
    }

    template<typename Meta>
    template<typename ParentType>
    void State<Meta>::createOrUpdateComponent(typename ParentType::Id parentId, ElementState&& item)
    {
        const ElementId id = static_cast<ElementId>(parentId);
        if (const auto existing = elements.find(id); existing != elements.end())
            existing->second = std::move(item);
        else
            elements.emplace(id, std::move(item));
    }

    template<typename Meta>
    auto State<Meta>::createNewItem(ElementId id, ElementState&& item) -> ElementId
    {
        const auto [_, inserted] = elements.try_emplace(id, std::move(item));
        if (!inserted)
        {
            throw std::logic_error("linear::State::createNewItem: duplicate element id");
        }
        return id;
    }
}
