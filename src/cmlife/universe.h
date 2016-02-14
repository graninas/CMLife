#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <functional>
#include <algorithm>

#include <functor.h>
#include <applicative.h>

using namespace std;

namespace cmlife
{

#define UT Universe<T>
#define UUT Universe<Universe<T>>
#define UUUT Universe<Universe<Universe<T>>>
#define UUUUT Universe<Universe<Universe<Universe<T>>>>
#define UB Universe<B>
#define UUB Universe<Universe<B>>
#define func function

template <typename T>
struct Universe
{
    std::vector<T> field;
    int position;

    int size() const
    {
        return field.size();
    }
};

template <typename T> UT
left(const UT& u)
{
    UT newU { u.field, u.position - 1 };
    if (u.position == 0)
        newU.position = u.size() - 1;
    return newU;
}

template <typename T> UT
right(const UT& u)
{
    UT newU { u.field, u.position + 1 };
    if (u.position == u.size() - 1)
        newU.position = 0;
    return newU;
}

// TODO: parallelize it here.
// TODO: functions tail, iterate...
template <typename T> std::vector<UT>
tailOfGen(int count,
    const std::function<UT(UT)>& generator,
    UT item)
{
    std::vector<UT> items;
    items.reserve(count);

    auto it = generator(item);
    for (int i = 0; i < count; ++i)
    {
        items.push_back(it);
        it = generator(it);
    }
    return items;
}

// TODO: parallelize it here.
// TODO: it's functional and imperative code mix.
template <typename T> UUT makeUniverse(
    const std::function<UT(UT)>& leftCreator,
    const std::function<UT(UT)>& rightCreator,
    const UT& u)
{
    std::vector<UT> all = std::vector<UT>();
    all.reserve(u.size());

    // TODO: optimize it.
    if (u.position > 0)
    {
        auto lefts = tailOfGen(u.position, leftCreator, u);
        all.insert(all.end(), lefts.begin(), lefts.end());
    }

    all.push_back(u);

    // TODO: optimize it.
    if (u.position < u.size() - 1)
    {
        auto rights = tailOfGen(u.size() - u.position - 1, rightCreator, u);
        all.insert(all.end(), rights.begin(), rights.end());
    }

    UUT newU { all, u.position };
    return newU;
}

template <typename T> UUT
    makeUniverseLR(const UT& u)
{
    const std::function<UT(UT)> leftCr = [](const UT& u1) {return left(u1); };
    const std::function<UT(UT)> rightCr = [](const UT& u1) {return right(u1); };

    return makeUniverse(leftCr, rightCr, u);
}

// Functor implementation

template <typename T> UT fmap(
    const std::function<T(T)>& f,
    const UT& u)
{
    UT newU;
    newU.position = u.position;
    newU.field = fp::map(f, u.field);
    return newU;
}

// Applicative implementation

template <typename T> UT pure(const T& t)
{
    UT u {{t}, 0};
    return u;
}

// Comonad implementation

template <typename T> T extract(const UT& u)
{
    return u.field[u.position]; // TODO: unsafe.
}

template <typename T> UUT duplicate(const UT& u)
{
    return makeUniverseLR(u);
}

template <typename T, typename B> UB extend(
    const std::function<B(UT)>& mappingExtractor,
    const UT& u)
{
    auto duplicated = duplicate(u);
    auto mapped = fp::map(mappingExtractor, duplicated.field);
    UB newU {mapped, u.position};
    return newU;
}

template <typename T> T extract2(const UUT& uut)
{
    return extract(extract(uut));
}

template <typename T> UUUUT duplicate2(const UUT& u)
{
    const func<UT(UT)> lCr1 = [](const UT& u1) { return left(u1); };
    const func<UT(UT)> rCr1 = [](const UT& u1) { return right(u1); };
    const func<UUT(UUT)> lCr2 = [](const UUT& u1) { return left(u1); };
    const func<UUT(UUT)> rCr2 = [](const UUT& u1) { return right(u1); };

    const func<UUT(UUT)> lFmapped1 = [=](const UUT& uux) { return fmap(lCr1, uux); };
    const func<UUT(UUT)> rFmapped1 = [=](const UUT& uux) { return fmap(rCr1, uux); };
    const func<UUUT(UUUT)> lFmapped2 = [=](const UUUT& uuux) { return fmap(lCr2, uuux); };
    const func<UUUT(UUUT)> rFmapped2 = [=](const UUUT& uuux) { return fmap(rCr2, uuux); };

    UUUT  shifted1 = makeUniverse(lFmapped1, rFmapped1, u);
    UUUUT shifted2 = makeUniverse(lFmapped2, rFmapped2, shifted1);

    return shifted2;
}

template <typename T> UUT fmap2(
    const func<T(UUT)>& mapExtr,
    const UUUUT& uuut)
{
    const func<UT(UUUT)> fmapper = [=](const UUUT& uuut2)
    {
        UT newUt;
        newUt.position = uuut2.position;
        newUt.field = fp::map(mapExtr, uuut2.field);
        return newUt;
    };

    UUT newU;
    newU.position = uuut.position;
    newU.field = fp::map(fmapper, uuut.field);
    return newU;
}

template <typename T> UUT extend2(
    const UUT& uut,
    const func<T(UUT)>& mapExtr)
{
    UUUUT duplicated = duplicate2(uut);
    UUT res = fmap2(mapExtr, duplicated);
    return res;
}

template <typename T> UUT stepWith(
    const func<T(UUT)>& mapExtr,
    const UUT& uut)
{
    return extend2(uut, mapExtr);
}



} // namespace cmlife


#endif // UNIVERSE_H
