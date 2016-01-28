#ifndef PARALLEL_UNIVERSE_H
#define PARALLEL_UNIVERSE_H

#include "universe.h"

#include <future>

namespace cmlife
{

#define FUUUUT std::future<UUUUT>
#define FUUUT std::future<UUUT>
#define FUUT std::future<UUT>
#define FUT std::future<UT>
#define FT std::future<T>

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
    newU.field = mapVector(fmapper, uuut.field);
    return newU;
}

template <typename T> FUUT extend2Par(
    FUUT& fuut,
    const func<T(UUT)>& mapExtr)
{
    return std::async(std::launch::async, [&]() // DANGER!!
    {
        fuut.wait();
        auto uut = fuut.get();
        return extend2(uut, mapExtr);
    });
}

template <typename T> FUUT stepWithPar(
    const func<T(UUT)>& mapExtr,
    FUUT& fuut)
{
    return extend2Par(fuut, mapExtr);
}

template <typename T> FUUT
   par(const UUT& uut)
{
    return std::async(std::launch::async, [=]() { return uut; });
}



} // namespace cmlife


#endif // PARALLEL_UNIVERSE_H
