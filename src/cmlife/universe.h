#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <functional>
#include <algorithm>
#include <utility>

#include <functor.h>
#include <applicative.h>

using namespace std;

namespace cmlife
{

/*
Could we do so?

template <class T> using UT = Universe<T>;
template <class T> using UUT = Universe<Universe<T>>;
template <class T> using UUUT = Universe<Universe<Universe<T>>>;
template <class T> using UUUUT = Universe<Universe<Universe<Universe<T>>>>;

// This leads to long UT<T>, but not short UT
*/

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

template <typename T> UUT makeUniverse(
    const func<UT(UT)>& leftCreator,
    const func<UT(UT)>& rightCreator,
    const UT& u)
{
    std::vector<UT> lefts  = tailOfGen(u.position, leftCreator, u);
    std::vector<UT> rights = tailOfGen(u.size() - u.position - 1, rightCreator, u);

    std::vector<UT> all;
    //all.swap(lefts);
    all.reserve(u.size());
    all.insert(all.end(), lefts.begin(), lefts.end());
    all.push_back(u);
    all.insert(all.end(), rights.begin(), rights.end());

    return { std::move(all), u.position };
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
    const func<T(T)>& f,
    const UT& u)
{
    return { fp::map(f, u.field), u.position };
}

// Applicative implementation

template <typename T> UT pure(const T& t)
{
    return {{t}, 0};
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

template <typename T, typename B>
UB extend(
    const func<B(UT)>& f,
    const UT& u)
{
    UUT duplicated = duplicate(u);
    return { fp::map(f, duplicated.field), u.position };
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

    return { fp::map(fmapper, uuut.field), uuut.position };
}

template <typename T> UUT extend2(
    const func<T(UUT)>& f,
    const UUT& uut)
{
    UUUUT duplicated = duplicate2(uut);
    return fmap2(f, duplicated);
}

/* 2 dims alias */
template <typename T> UUT stepWith(
    const func<T(UUT)>& f,
    const UUT& uut)
{
    return extend2(f, uut);
}

/* 1 dim alias */
template <typename T> UT stepWith(
    const func<T(UT)>& f,
    const UT& ut)
{
    return extend(f, ut);
}


} // namespace cmlife


#endif // UNIVERSE_H
