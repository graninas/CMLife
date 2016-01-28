#ifndef UTILS_H
#define UTILS_H

#include "universe.h"

#include <algorithm>

namespace cmlife {


template <typename T> Universe<T>
    fromVector(const std::vector<T>& v)
    {
        Universe<T> u;
        u.field = v;
        u.position = 0;
        return u;
    }

// Tip: accumulate can be replaced by parralel std::experimental::par::reduce.
template <typename T> Universe<Universe<T>>
    fromVector2(const std::vector<std::vector<T>>& v)
    {
        auto u = std::accumulate(v.begin(), v.end(), Universe<Universe<T>>(),
            [](const Universe<Universe<T>>& u, const std::vector<T>& it)
            {
                Universe<Universe<T>> newU = u;
                newU.field.push_back(fromVector(it));
                return newU;
            });

        u.position = 0;
        return u;
    }


template <typename T> std::vector<std::vector<T>>
toVector2(const Universe<Universe<T>>& u)
{
    std::vector<std::vector<T>> v;
    v.reserve(u.size());
        for (int i = 0; i < u.size(); ++i)
        {
            v.push_back(u.field[i].field);
        }
    return v;
}

} // namespace cmlife


#endif // UTILS_H
