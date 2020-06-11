
#include <string>

#include <fmt/format.h>
#include <fmt/chrono.h>

#include "concepts.hpp"

namespace sfy
{
    inline auto to_string(Arithmetic auto a) noexcept
    {
        return fmt::format("{}", a);
    }

    inline auto to_string(Character auto c, bool quoted = true) noexcept
    {
        return quoted ? fmt::format("'{}'", c) : fmt::format("{}", c);
    }

    inline auto to_string(String auto s, bool quoted = true) noexcept
    {
        return quoted ? fmt::format(R"("{}")", s) : fmt::format("{}", s);
    }

    // Begin: Forward declarations.
    auto to_string(Pair auto p) noexcept;

    auto to_string(Tuple auto t) noexcept;

    template <Ratio R>
    auto to_string(R) noexcept;

    auto to_string(Complex auto c) noexcept;

    auto to_string(ChronoDuration auto cd) noexcept;

    template <ChronoTimePoint CTP>
    auto to_string(CTP ctp) noexcept;

    auto to_string(ValueContainer auto&& container) noexcept;

    auto to_string(KeyValueContainer auto&& container) noexcept;

    // Needed for C-style arrays.
    template <typename T>
    concept Sfyable =
    requires(T t) {
        to_string(t);
    };

    template <typename T, std::size_t N>
    requires Sfyable<T> && (!Character<T>)
    auto to_string(T(& c_array)[N]) noexcept;
    // End: Forward declarations.

    inline auto to_string(Pair auto p) noexcept
    {
        return fmt::format("({}, {})", to_string(p.first), to_string(p.second));
    }

    namespace detail
    {
        template <size_t... I>
        inline auto tuple_impl(Tuple auto t, std::index_sequence<I...>)
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

    inline auto to_string(Tuple auto t) noexcept
    {
        return detail::to_string(t);
    }

    template <Ratio R>
    inline auto to_string(R) noexcept
    {
        return fmt::format("{}/{}", R::num, R::den);
    }

    inline auto to_string(Complex auto c) noexcept
    {
        return fmt::format("{} + {}i", to_string(c.real()), to_string(c.imag()));
    }

    inline auto to_string(ChronoDuration auto cd) noexcept
    {
        return fmt::format("{}", cd);
    }

    template <ChronoTimePoint CTP>
    inline auto to_string(CTP ctp) noexcept
    {
        auto tt = CTP::clock::to_time_t(ctp);
        return fmt::format("{}", to_string(ctime(&tt), false));
    }

    auto to_string(ValueContainer auto&& container) noexcept
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

    auto to_string(KeyValueContainer auto&& container) noexcept
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
}