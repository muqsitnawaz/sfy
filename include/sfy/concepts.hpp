
#include <iterator>

#include <range/v3/range/concepts.hpp>

#include "alias.hpp"
#include "traits.hpp"

template <typename T1, typename T2>
concept Same_t = std::is_same_v<T1, T2>;

template <typename T>
concept Fundamental = std::is_fundamental_v<T>;

template <typename T>
concept Pair = is_pair_v<T>();

template <typename T>
concept Tuple = is_tuple_v<T>();

template <typename T>
concept Container =
requires(T t) {
    typename Iterator_t<T>;
    typename Value_t<T>;

    { std::begin(t) };
    { std::end(t) };

    requires Same_t<Value_t<T>, Value_t<Iterator_t<T>>>;
};

template <typename T>
concept Range = ranges::view_<T> || Container<T>;