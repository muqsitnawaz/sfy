
template <typename T>
using Key_t = typename std::decay_t<T>::key_type;

template <typename T>
using Mapped_t = typename std::decay_t<T>::mapped_type;

template <typename T>
using Value_t = typename std::decay_t<T>::value_type;

template <typename T>
using Size_t = typename std::decay_t<T>::size_type;

template <typename T>
using Iterator_t = typename std::decay_t<T>::iterator;

template <typename T>
using Iterator_c = typename std::iterator_traits<T>::iterator_category;