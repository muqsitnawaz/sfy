
template <typename T>
using Key_t = typename T::key_type;

template <typename T>
using Mapped_t = typename T::mapped_type;

template <typename T>
using Value_t = typename T::value_type;

template <typename T>
using Size_t = typename T::size_type;

template <typename T>
using Iterator_t = typename T::iterator;

template <typename T>
using Iterator_c = typename std::iterator_traits<T>::iterator_category;