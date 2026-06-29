#pragma once

#include <functional>
#include <optional>
#include <type_traits>

#include "NewGame/Core/Model/Complex.h"
#include "NewGame/Core/Operations/ContextData.h"

namespace swexp::core::manipulation::detail {
    template<typename Meta, typename = void>
    struct actions {
        using type = typename Meta::BaseActions;
    };

    template<typename Meta>
    struct actions<Meta, std::void_t<typename Meta::Actions>> {
        using type = typename Meta::Actions;
    };
}

namespace swexp::core::manipulation {
    template<typename Meta>
    using call = typename detail::actions<Meta>::type;

    template<typename Meta>
    bool exists(api::context::Reading, typename Meta::Id);

    template<typename Meta>
    auto get(api::context::Reading, typename Meta::Id) -> const typename Meta::State&;

    template<typename Meta>
    auto get(api::context::Writing, typename Meta::Id) -> typename Meta::State&;

    template<typename Meta>
    auto try_get(api::context::Reading, typename Meta::Id)
        -> std::optional<std::reference_wrapper<const typename Meta::State>>;

    template<typename Meta>
    auto try_get(api::context::Writing, typename Meta::Id)
        -> std::optional<std::reference_wrapper<typename Meta::State>>;
}

// Impl
namespace swexp::core::manipulation {
    template<typename Meta>
    bool exists(api::context::Reading context, typename Meta::Id id)
    {
        const auto& elements = context.state.template line<Meta>().elements;
        return elements.find(id) != elements.end();
    }

    template<typename Meta>
    auto get(api::context::Reading context, typename Meta::Id id) -> const typename Meta::State&
    {
        return context.state.template line<Meta>().elements.at(id);
    }

    template<typename Meta>
    auto get(api::context::Writing context, typename Meta::Id id) -> typename Meta::State&
    {
        return context.state.template line<Meta>().elements.at(id);
    }

    template<typename Meta>
    auto try_get(api::context::Reading context, typename Meta::Id id)
        -> std::optional<std::reference_wrapper<const typename Meta::State>>
    {
        const auto& elements = context.state.template line<Meta>().elements;
        const auto item = elements.find(id);
        if (item == elements.end())
            return std::nullopt;

        return std::cref(item->second);
    }

    template<typename Meta>
    auto try_get(api::context::Writing context, typename Meta::Id id)
        -> std::optional<std::reference_wrapper<typename Meta::State>>
    {
        auto& elements = context.state.template line<Meta>().elements;
        const auto item = elements.find(id);
        if (item == elements.end())
            return std::nullopt;

        return std::ref(item->second);
    }
}

