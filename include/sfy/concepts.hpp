
#include <iterator>

#include "alias.hpp"
#include "traits.hpp"

template <typename T1, typename T2>
concept Same_t = std::is_same_v<T1, T2>;

template <typename T>
concept RandomAccessIterator = std::is_same_v<Iterator_category<T>, std::random_access_iterator_tag>;

template <typename T>
concept BidirectionalIterator = std::is_same_v<Iterator_category<T>, std::bidirectional_iterator_tag>;

template <typename T>
concept ForwardIterator = std::is_same_v<Iterator_category<T>, std::forward_iterator_tag>;

template <typename T>
concept Fundamental = std::is_fundamental_v<T>;

template <typename T>
concept Pair = is_pair_v<T>();

template <typename T>
concept Tuple = is_tuple_v<T>();

template <typename T>
concept Sequence =
requires(T t) {
    typename Value_t<T>;
    typename Size_t<T>;

    typename Iterator_t<T>;

    { std::begin(t) };
    { std::end(t) };

    requires RandomAccessIterator<Iterator_t<T>>;
    requires Same_t<Value_t<T>, Value_t<Iterator_t<T>>>;
};

template <typename T>
concept OrderedValues =
requires(T t) {
    typename Key_t<T>;
    typename Value_t<T>;
    typename Size_t<T>;

    typename Iterator_t<T>;

    { std::begin(t) };
    { std::end(t) };

    requires BidirectionalIterator<Iterator_t<T>>;
    requires Same_t<Value_t<T>, Value_t<Iterator_t<T>>>;
};

template <typename T>
concept OrderedKeyValues =
requires(T t) {
    typename Mapped_t<T>;

    requires OrderedValues<T>;
};

template <typename T>
concept UnorderedValues =
requires(T t)
{
    typename Key_t<T>;
    typename Value_t<T>;
    typename Size_t<T>;

    typename Iterator_t<T>;

    { std::begin(t) };
    { std::end(t) };

    requires ForwardIterator<Iterator_t<T>>;
    requires Same_t<Value_t<T>, Value_t<Iterator_t<T>>>;
};

template <typename T>
concept UnorderedKeyValues =
requires(T t)
{
    typename Mapped_t<T>;

    requires UnorderedValues<T>;
};

template <typename T>
concept ValueContainer = Sequence<T>
                         || (OrderedValues<T> && !OrderedKeyValues<T>)
                         || (UnorderedValues<T> && !UnorderedKeyValues<T>);

template <typename T>
concept KeyValueContainer = OrderedKeyValues<T> || UnorderedKeyValues<T>;