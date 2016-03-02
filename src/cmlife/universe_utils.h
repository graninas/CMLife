#ifndef UNIVERSE_UTILS_H
#define UNIVERSE_UTILS_H

#include "universe.h"

#include <algorithm>

namespace cmlife
{

template <typename A>
UA fromVector(const std::vector<A>& v)
{
    return {v, 0};
}

// Tip: accumulate can be replaced by parralel std::experimental::par::reduce.
template <typename A>
UUA fromVector2(const std::vector<std::vector<A>>& v)
{
    auto u = std::accumulate(v.begin(), v.end(), UUA(),
        [](const UUA& u, const std::vector<A>& it)
        {
            UUA newU = u;
            newU.field.push_back(fromVector(it));
            return newU;
        });
     u.position = 0;
    return u;
}

template <typename A>
std::vector<std::vector<A>> toVector2(const UUA& u)
{
    std::vector<std::vector<A>> v;
    v.reserve(u.size());
        for (int i = 0; i < u.size(); ++i)
        {
            v.push_back(u.field[i].field);
        }
    return v;
}

} // namespace cmlife


#endif // UNIVERSE_UTILS_H
