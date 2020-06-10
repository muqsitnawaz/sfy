
#pragma once

#include <boost/type_index.hpp>

namespace sfy
{
    template <typename T>
    inline auto type()
    {
        return boost::typeindex::type_id_with_cvr<T>().pretty_name();
    }

    inline auto type(auto&& var)
    {
        return boost::typeindex::type_id_with_cvr<decltype(var)>().pretty_name();
    }
}