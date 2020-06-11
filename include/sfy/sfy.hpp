
#include <string>

#include <fmt/format.h>
#include <fmt/chrono.h>

#include "concepts.hpp"

namespace sfy
{
    template <Arithmetic A>
    inline auto to_string(A a) noexcept
    {
        return fmt::format("{}", a);
    }

    template <Character C>
    inline auto to_string(C c, bool quoted = true) noexcept
    {
        return quoted ? fmt::format("'{}'", c) : fmt::format("{}", c);
    }

    template <String S>
    inline auto to_string(S s, bool quoted = true) noexcept
    {
        return quoted ? fmt::format(R"("{}")", s) : fmt::format("{}", s);
    }

    // Begin: Forward declarations.
    template <Tuple T>
    inline auto to_string(T t) noexcept;

    template <typename T, std::size_t N>
    requires Sfyable<T> && (!Character<T>)
    auto to_string(T(& c_array)[N]) noexcept;

    template <ValueContainer C>
    auto to_string(C container) noexcept;

    template <KeyValueContainer C>
    auto to_string(C container) noexcept;
    // End: Forward declarations.

    template <Pair P>
    inline auto to_string(P p) noexcept
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

        template <typename...Ts>
        inline auto to_string(std::tuple<Ts...> t)
        {
            return tuple_impl(t, std::make_index_sequence<sizeof...(Ts)>());
        }
    }

    template <Tuple T>
    inline auto to_string(T t) noexcept
    {
        return detail::to_string(t);
    }

    template <Ratio R>
    inline auto to_string(R) noexcept
    {
        return fmt::format("{}/{}", R::num, R::den);
    }

    template <Complex C>
    inline auto to_string(C c) noexcept
    {
        return fmt::format("{} + {}i", to_string(c.real()), to_string(c.imag()));
    }

    template <ChronoDuration CD>
    inline auto to_string(CD cd) noexcept
    {
        return fmt::format("{}", cd);
    }

    template <ChronoTimePoint CTP>
    inline auto to_string(CTP ctp) noexcept
    {
        auto tt = CTP::clock::to_time_t(ctp);
        return fmt::format("{}", to_string(ctime(&tt), false));
    }

    template <typename T, std::size_t N>
    requires Sfyable<T> && (!Character<T>)
    auto to_string(T(& c_array)[N]) noexcept
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
    auto to_string(C container) noexcept
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
    auto to_string(C container) noexcept
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