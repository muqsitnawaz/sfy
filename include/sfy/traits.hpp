
#include <type_traits>

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

    template <typename>
    struct is_std_basic_string : std::false_type {};

    template <typename C, typename T, typename A>
    struct is_std_basic_string<std::basic_string<C, T, A>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_std_basic_string_v() noexcept
    {
        return is_std_basic_string<T>::value;
    }

    template <typename>
    struct is_std_pair : std::false_type {};

    template <typename T1, typename T2>
    struct is_std_pair<std::pair<T1, T2>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_pair_v() noexcept
    {
        return is_std_pair<T>::value/* || is_ranges_pair<T>::value*/;
    }

    template <typename>
    struct is_std_tuple : std::false_type {};

    template <typename...Ts>
    struct is_std_tuple<std::tuple<Ts...>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_tuple_v() noexcept
    {
        return is_std_tuple<T>::value;
    }

    template <typename>
    struct is_c_arr : std::false_type {};

    template <typename T, std::size_t N>
    struct is_c_arr<T(&)[N]> : std::true_type {};

    template <typename T>
    inline constexpr bool is_c_arr_v() noexcept
    {
        return std::is_pointer_v<T>;
    }
}