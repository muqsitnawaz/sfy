
#include <string>

#include <fmt/format.h>

#include "concepts.hpp"
#include "type.hpp"

namespace sfy
{
    // TODO: Add overloads for std::string type.
    template <Fundamental F>
    inline auto to_string(F f)
    {
        return fmt::format("{}", f);
    }

    template <Pair P>
    inline auto to_string(P p)
    {
        return fmt::format("({}, {})", p.first, p.second);
    }

    template <Tuple T, size_t... I>
    inline auto tuple_impl(T t, std::index_sequence<I...>)
    {
        std::string ret = "(";
        (..., (ret = I == 0 ? (fmt::format("{}{}", ret, to_string(std::get<I>(t))))
                            : (fmt::format("{}, {}", ret, to_string(std::get<I>(t))))));
        return fmt::format("{})", ret);
    }

    template <typename...Ts>
    inline auto to_string(std::tuple<Ts...> t)
    {
        return tuple_impl(t, std::make_index_sequence<sizeof...(Ts)>());
    }

    template <String S>
    inline std::string to_string(S s) noexcept
    {
        return s;
    }

    template <KeyValueContainer C>
    std::string to_string(C container) noexcept;

    template <ValueContainer C>
    std::string to_string(C container) noexcept
    {
        std::string ret = "[";
        for (size_t ctr = 0; auto elem : container)
        {
            ret = ctr == 0 ? fmt::format("{}{}", ret, to_string(elem))
                           : fmt::format("{}, {}", ret, to_string(elem));
            ctr += 1;
        }
        return fmt::format("{}]", ret);
    }

    template <KeyValueContainer C>
    std::string to_string(C container) noexcept
    {
        std::string ret;
        for (size_t ctr = 0; auto elem : container)
        {
            ret = ctr == 0 ? fmt::format("{}{}: {}", ret, to_string(elem.first), to_string(elem.second))
                           : fmt::format("{}, {}: {}", ret, to_string(elem.first), to_string(elem.second));
            ctr += 1;
        }
        return fmt::format("{{{}}}", ret);
    }
}