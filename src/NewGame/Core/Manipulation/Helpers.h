#include <type_traits>

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
}