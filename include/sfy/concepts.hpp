
#include <iterator>

#include "alias.hpp"
#include "traits.hpp"

namespace sfy
{
    template <typename T>
    concept RandomAccessIterator = std::is_same_v<Iterator_c<T>, std::random_access_iterator_tag>;

    template <typename T>
    concept BidirectionalIterator = std::is_same_v<Iterator_c<T>, std::bidirectional_iterator_tag>;

    template <typename T>
    concept ForwardIterator = std::is_same_v<Iterator_c<T>, std::forward_iterator_tag>;

    template <typename T>
    concept Iterator = RandomAccessIterator<Iterator_t<T>> ||
                       BidirectionalIterator<Iterator_t<T>> ||
                       ForwardIterator<Iterator_t<T>>;

    template <typename T>
    concept Arithmetic = is_arithmetic_v<T>();

    template <typename T>
    concept Character = is_character_v<T>();

    template <typename T>
    concept String = is_c_str_v<T>() || is_std_basic_string_v<T>;

    template <typename T>
    concept Pair = is_pair_v<T>;

    template <typename T>
    concept Tuple = is_tuple_v<T>;

    template <typename T>
    concept Ratio = is_std_ratio_v<T>;

    template <typename T>
    concept Complex = is_std_complex_v<T>;

    template <typename T>
    concept ChronoDuration = is_std_chrono_duration_v<T>;

    template <typename T>
    concept ChronoTimePoint = is_std_chrono_time_point_v<T>;

    template <typename T>
    concept ValueContainer =
    requires(T cont)
    {
        typename Value_t<T>;
        typename Size_t<T>;

        typename Iterator_t<T>;

        { std::begin(cont) };
        { std::end(cont) };

        requires Iterator<T>;
        requires std::is_same_v<Value_t<T>, Value_t<Iterator_t<T>>>;
        requires !String<T>;
    };

    template <typename T>
    concept KeyValueContainer = ValueContainer<T> &&
                                requires(T cont) {
                                    typename Key_t<T>;
                                    typename Mapped_t<T>;
                                };
}