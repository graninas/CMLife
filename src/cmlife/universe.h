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

template <typename T> Universe<T>
left(const Universe<T>& u)
{
    Universe<T> newU { u.field, u.position - 1 };
    if (u.position == 0)
        newU.position = u.size() - 1;
    return newU;
}

template <typename T> Universe<T>
right(const Universe<T>& u)
{
    Universe<T> newU { u.field, u.position + 1 };
    if (u.position == u.size() - 1)
        newU.position = 0;
    return newU;
}

// TODO: functions tail, iterate...
template <typename T> std::vector<Universe<T>>
tailOfGen(int count,
    const std::function<Universe<T>(Universe<T>)>& generator,
    Universe<T> item)
{
    std::vector<Universe<T>> items;
    items.reserve(count);

    auto it = generator(item);
    for (int i = 0; i < count; ++i)
    {
        items.push_back(it);
        it = generator(it);
    }
    return items;
}

// TODO: it's functional and imperative code mix.
template <typename T> Universe<Universe<T>>
makeUniverse(
    const std::function<Universe<T>(Universe<T>)>& leftCreator,
    const std::function<Universe<T>(Universe<T>)>& rightCreator,
    const Universe<T>& u)
{
    std::vector<Universe<T>> all = std::vector<Universe<T>>();
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

    Universe<Universe<T>> newU { all, u.position };
    return newU;
}

template <typename T> Universe<Universe<T>>
    makeUniverseLR(const Universe<T>& u)
{
    const std::function<Universe<T>(Universe<T>)> leftCr = [](const Universe<T>& u1) {return left(u1); };
    const std::function<Universe<T>(Universe<T>)> rightCr = [](const Universe<T>& u1) {return right(u1); };

    return makeUniverse(leftCr, rightCr, u);
}

// Functor implementation

template <typename T>
Universe<T> fmap(
    const std::function<T(T)>& f,
    const Universe<T>& u)
{
    Universe<T> newU;
    newU.position = u.position;
    newU.field = mapVector(f, u.field);
    return newU;
}

// Applicative implementation

template <typename T> Universe<T> pure(const T& t)
{
    Universe<T> u {{t}, 0};
    return u;
}

// Comonad implementation

template <typename T> T extract(const Universe<T>& u)
{
    return u.field[u.position]; // TODO: unsafe.
}

template <typename T> UUT duplicate(const Universe<T>& u)
{
    return makeUniverseLR(u);
}

template <typename T, typename B> Universe<B> extend(
    const std::function<B(Universe<T>)>& mappingExtractor,
    const Universe<T>& u)
{
    auto duplicated = duplicate(u);
    auto mapped = mapVector(mappingExtractor, duplicated.field);
    Universe<B> newU {mapped, u.position};
    return newU;
}

template <typename T> T extract2(const Universe<Universe<T>>& u)
{
    return extract(extract(u));
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
        newUt.field = mapVector(mapExtr, uuut2.field);
        return newUt;
    };

    UUT newU;
    newU.position = uuut.position;
    newU.field = mapVector(fmapper, uuut.field);
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
