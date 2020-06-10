
#include <string>

#include <fmt/format.h>

#include "concepts.hpp"
#include "type.hpp"

namespace sfy
{
    template <Arithmetic A>
    inline auto to_string(A a)
    {
        return fmt::format("{}", a);
    }

    template <Character C>
    inline auto to_string(C c)
    {
        return fmt::format("'{}'", c);
    }

    template <String S>
    inline std::string to_string(S s) noexcept
    {
        return fmt::format(R"("{}")", s);
    }

    // Forward declarations.
    template <ValueContainer C>
    std::string to_string(C container) noexcept;

    template <KeyValueContainer C>
    std::string to_string(C container) noexcept;

    template <typename...Ts>
    inline auto to_string(std::tuple<Ts...> t);

    template <Pair P>
    inline auto to_string(P p)
    {
        return fmt::format("({}, {})", to_string(p.first), to_string(p.second));
    }

    namespace detail
    {
        template <Tuple T, size_t... I>
        inline auto tuple_impl(T t, std::index_sequence<I...>)
        {
            std::string ret = "(";
            (..., (ret = I == 0 ? (fmt::format("{}{}", ret, to_string(std::get<I>(t))))
                                : (fmt::format("{}, {}", ret, to_string(std::get<I>(t))))));
            return fmt::format("{})", ret);
        }
    }

    template <typename...Ts>
    inline auto to_string(std::tuple<Ts...> t)
    {
        return detail::tuple_impl(t, std::make_index_sequence<sizeof...(Ts)>());
    }

    template <typename T, std::size_t N>
    requires Sfyable<T> && (!Character<T>)
    std::string to_string(T(& c_array)[N]) noexcept
    {
        std::string ret = "[";
        for (size_t i = 0; i < N; ++i)
        {
            ret = i == 0 ? fmt::format("{}{}", ret, to_string(c_array[i]))
                         : fmt::format("{}, {}", ret, to_string(c_array[i]));
        }
        return fmt::format("{}]", ret);
    }

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