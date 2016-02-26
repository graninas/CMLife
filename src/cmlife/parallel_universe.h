#ifndef PARALLEL_UNIVERSE_H
#define PARALLEL_UNIVERSE_H

#include "universe.h"
#include "par.h"

#include <future>

namespace cmlife
{

/*
 * Parallel duplicate2Par slows down the computations against parallel fmap2Par only (2 times).
template <typename T> UUUUT duplicate2Par(const UUT& u)
{
    const func<UT(UT)> lCr1 = [](const UT& u1) { return left(u1); };
    const func<UT(UT)> rCr1 = [](const UT& u1) { return right(u1); };
    const func<UUT(UUT)> lCr2 = [](const UUT& u1) { return left(u1); };
    const func<UUT(UUT)> rCr2 = [](const UUT& u1) { return right(u1); };

    const func<UUT(UUT)> lFmapped1 = [=](const UUT& uux) { return fmapPar(lCr1, uux); };
    const func<UUT(UUT)> rFmapped1 = [=](const UUT& uux) { return fmapPar(rCr1, uux); };
    const func<UUUT(UUUT)> lFmapped2 = [=](const UUUT& uuux) { return fmapPar(lCr2, uuux); };
    const func<UUUT(UUUT)> rFmapped2 = [=](const UUUT& uuux) { return fmapPar(rCr2, uuux); };

    UUUT  shifted1 = makeUniverse(lFmapped1, rFmapped1, u);
    UUUUT shifted2 = makeUniverse(lFmapped2, rFmapped2, shifted1);

    return shifted2;
}
*/

template <typename T> UUT fmap2Par(
    const func<T(UUT)>& f,
    const UUUUT& uuut)
{
    const func<UT(UUUT)> fmapper = [=](const UUUT& uuut2)
    {
        UT newUt;
        newUt.position = uuut2.position;
        newUt.field = fp::map(f, uuut2.field);
        return newUt;
    };

    return { mapPar(fmapper, uuut.field), uuut.position };
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
    std::vector<B> mapped = mapPar(f, duplicated.field);
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
