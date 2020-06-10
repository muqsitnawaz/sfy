
#include <vector>
#include <string>

#include <fmt/format.h>

#include "concepts.hpp"

namespace sfy
{
    template <Fundamental F>
    auto to_string(F f)
    {
        return fmt::format("{}", f);
    }

    template <Pair P>
    auto to_string(P p)
    {
        return fmt::format("({}, {})", p.first, p.second);
    }

    template <Tuple T, size_t... I>
    auto tuple_impl(T t, std::index_sequence<I...>)
    {
        std::string ret = "(";
        (..., (ret = I == 0 ? (fmt::format("{}{}", ret, to_string(std::get<I>(t))))
                            : (fmt::format("{}, {}", ret, to_string(std::get<I>(t))))));
        return fmt::format("{})", ret);
    }

    template <typename...Ts>
    auto to_string(std::tuple<Ts...> t)
    {
        return tuple_impl(t, std::make_index_sequence<sizeof...(Ts)>());
    }

    template <Range Rng>
    std::string to_string(Rng rng) noexcept
    {
        std::string ret = "[";
        for (size_t ctr = 0; auto elem : rng)
        {
            ret = ctr == 0 ? fmt::format("{}{}", ret, to_string(elem))
                           : fmt::format("{}, {}", ret, to_string(elem));
            ctr += 1;
        }
        return fmt::format("{}]", ret);
    }
}