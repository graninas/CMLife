#ifndef PARALLEL_UNIVERSE_H
#define PARALLEL_UNIVERSE_H

#include "universe.h"
#include "map.h"
#include "parallel_map.h"

#include <future>

namespace cmlife
{

template <typename A>
UUA fmap2Par(
    const func<A(UUA)>& f,
    const UUUUA& uuu)
{
    const func<UA(UUUA)> f2 = [=](const UUUA& uuu2)
    {
        UA newU;
        newU.position = uuu2.position;
        newU.field = fp::map(f, uuu2.field);
        return newU;
    };

    return { fp::mapPar(f2, uuu.field), uuu.position };
}

template <typename A> UUA extend2Par(
    const UUA& uu,
    const func<A(UUA)>& f)
{
    auto duplicated = duplicate2(uu);
    return fmap2Par(f, duplicated);
}

template <typename A, typename B>
UB extendPar(
    const func<B(UA)>& f,
    const UA& u)
{
    UUA duplicated = duplicate(u);
    std::vector<B> mapped = fp::mapPar(f, duplicated.field);
    return { std::move(mapped), u.position };
}

template <typename A> UA stepWithPar(
    const func<A(UA)>& f,
    UA& u)
{
    return extendPar(f, u);
}

template <typename A> UUA stepWith2Par(
    const func<A(UUA)>& f,
    UUA& uu)
{
    return extend2Par(uu, f);
}

} // namespace cmlife


#endif // PARALLEL_UNIVERSE_H
