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

template <typename T> UUT extend2Par(
    const UUT& uut,
    const func<T(UUT)>& f)
{
    UUUUT duplicated = duplicate2(uut);
    return fmap2Par(f, duplicated);
}

template <typename T, typename B>
UB extendPar(
    const func<B(UT)>& f,
    const UT& u)
{
    UUT duplicated = duplicate(u);
    std::vector<B> mapped = fp::mapPar(f, duplicated.field);
    return { std::move(mapped), u.position };
}

template <typename T> UT stepWithPar(
    const func<T(UT)>& f,
    UT& ut)
{
    return extendPar(f, ut);
}

template <typename T> UUT stepWith2Par(
    const func<T(UUT)>& f,
    UUT& uut)
{
    return extend2Par(uut, f);
}

} // namespace cmlife


#endif // PARALLEL_UNIVERSE_H
