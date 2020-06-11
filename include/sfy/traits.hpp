
#include <type_traits>

#include <complex>

/*#include <range/v3/range/concepts.hpp>

template <typename>
struct is_ranges_pair : std::false_type {};

template <typename T1, typename T2>
struct is_ranges_pair<ranges::common_pair<T1, T2>> : std::true_type {};*/

namespace sfy
{
    template <typename T>
    inline constexpr bool is_character_v() noexcept
    {
        auto is_char = std::is_same_v<T, char> ||
                       std::is_same_v<T, signed char> || std::is_same_v<T, unsigned char> ||
                       std::is_same_v<T, wchar_t>;
#ifndef _LIBCPP_NO_HAS_CHAR8_T
        is_char = is_char || std::is_same_v<T, char8_t>;
#endif
#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS
        is_char = is_char || std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>;
#endif
        return is_char;
    }

    template <typename T>
    inline constexpr bool is_arithmetic_v() noexcept
    {
        return std::is_arithmetic_v<T> && !is_character_v<T>();
    }

    template <typename T>
    inline constexpr bool is_c_str_v() noexcept
    {
        return std::is_same_v<std::decay_t<T>, char*> || std::is_same_v<std::decay_t<T>, char const*>;
    }

    // Begin: std::string.
    template <typename>
    struct is_std_basic_string : std::false_type {};

    template <typename C, typename T, typename A>
    struct is_std_basic_string<std::basic_string<C, T, A>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_std_basic_string_v() noexcept
    {
        return is_std_basic_string<T>::value;
    }
    // End: std::string.

    // Begin: std::pair.
    template <typename>
    struct is_std_pair : std::false_type {};

    template <typename T1, typename T2>
    struct is_std_pair<std::pair<T1, T2>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_pair_v() noexcept
    {
        return is_std_pair<T>::value/* || is_ranges_pair<T>::value*/;
    }
    // End: std::pair.

    // Begin: std::tuple.
    template <typename>
    struct is_std_tuple : std::false_type {};

    template <typename...Ts>
    struct is_std_tuple<std::tuple<Ts...>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_tuple_v() noexcept
    {
        return is_std_tuple<T>::value;
    }
    // End: std::tuple.

    // Begin: std::ratio.
    template <typename>
    struct is_std_ratio : std::false_type {};

    template <intmax_t Num, intmax_t Den>
    struct is_std_ratio<std::ratio<Num, Den>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_std_ratio_v() noexcept
    {
        return is_std_ratio<T>();
    }
    // End: std::ratio.

    // Begin: std::complex.
    template <typename>
    struct is_std_complex : std::false_type {};

    template <typename T>
    struct is_std_complex<std::complex<T>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_std_complex_v() noexcept
    {
        return is_std_complex<T>();
    }
    // End: std::complex.

    // Begin: std::chrono::duration.
    template <typename T>
    struct is_std_chrono_duration : std::false_type {};

    template <typename R, typename P>
    struct is_std_chrono_duration<std::chrono::duration<R, P>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_std_chrono_duration_v() noexcept
    {
        return is_std_chrono_duration<T>();
    }
    // End: std::chrono::duration.
}