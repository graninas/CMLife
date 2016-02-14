#ifndef PARALLEL_UNIVERSE_H
#define PARALLEL_UNIVERSE_H

#include "universe.h"
#include "par.h"

#include <future>

namespace cmlife
{


template <typename T> UUT fmap2Par(
    const func<T(UUT)>& mapExtr,
    const UUUUT& uuut)
{
    const func<UT(UUUT)> fmapper = [=](const UUUT& uuut2)
    {
        UT newUt;
        newUt.position = uuut2.position;
        newUt.field = mapVector(mapExtr, uuut2.field);
        return newUt;
    };

    UUT newU;
    newU.position = uuut.position;
    newU.field = mapVectorPar(fmapper, uuut.field);
    return newU;
}

template <typename T> UUT extend2Par(
    const UUT& uut,
    const func<T(UUT)>& mapExtr)
{
    UUUUT duplicated = duplicate2(uut);
    UUT res = fmap2Par(mapExtr, duplicated);
    return res;
}

template <typename T> UUT stepWithPar(
    const func<T(UUT)>& mapExtr,
    UUT& uut)
{
    return extend2Par(uut, mapExtr);
}



} // namespace cmlife


#endif // PARALLEL_UNIVERSE_H
