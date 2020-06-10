
#include <type_traits>

/*
#include <range/v3/range/concepts.hpp>


template <typename>
struct is_ranges_pair : std::false_type {};

template <typename T1, typename T2>
struct is_ranges_pair<ranges::common_pair<T1, T2>> : std::true_type {};
*/

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