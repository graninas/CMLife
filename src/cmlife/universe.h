#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <functional>
#include <algorithm>
#include <utility>

#include <map.h>

using namespace std;

namespace cmlife
{

/*
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

#define UA Universe<A>
#define UUA Universe<Universe<A>>
#define UUUA Universe<Universe<Universe<A>>>
#define UUUUA Universe<Universe<Universe<Universe<A>>>>
#define UB Universe<B>
#define UUB Universe<Universe<B>>
#define UUUB Universe<Universe<Universe<B>>>
#define UUUUB Universe<Universe<Universe<Universe<B>>>>
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

template <typename T>
UT left(const UT& u)
{
    UT newU { u.field, u.position - 1 };
    if (u.position == 0)
        newU.position = u.size() - 1;
    return newU;
}

template <typename T>
UT right(const UT& u)
{
    UT newU { u.field, u.position + 1 };
    if (u.position == u.size() - 1)
        newU.position = 0;
    return newU;
}

template <typename T>
std::vector<UT> tailOfGen(
    int count,
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

template <typename T>
UUT makeUniverse(
    const func<UT(UT)>& leftCreator,
    const func<UT(UT)>& rightCreator,
    const UT& u)
{
    std::vector<UT> lefts  = tailOfGen(u.position, leftCreator, u);
    std::vector<UT> rights = tailOfGen(u.size() - u.position - 1, rightCreator, u);

    std::vector<UT> all;
    all.reserve(u.size());
    all.insert(all.end(), lefts.begin(), lefts.end());
    all.push_back(u);
    all.insert(all.end(), rights.begin(), rights.end());

    return { std::move(all), u.position };
}

template <typename T>
UUT makeUniverseLR(const UT& u)
{
    const std::function<UT(UT)> leftCr = [](const UT& u1) {return left(u1); };
    const std::function<UT(UT)> rightCr = [](const UT& u1) {return right(u1); };

    return makeUniverse(leftCr, rightCr, u);
}

// Functor implementation

template <typename A, typename B>
UB fmap(
    const func<B(A)>& f,
    const UA& u)
{
    return { fp::map(f, u.field), u.position };
}

template <typename A, typename B>
UUB fmap(
    const func<B(UUA)>& f,
    const UUUUA& uuu)
{
    const func<UB(UUUA)> f2 = [=](const UUUA& uuu2)
    {
        UB newUt;
        newUt.position = uuu2.position;
        newUt.field = fp::map(f, uuu2.field);
        return newUt;
    };

    return { fp::map(f2, uuu.field), uuu.position };
}

// Applicative implementation

template <typename T>
UT pure(const T& t)
{
    return {{t}, 0};
}

// Comonad implementation

template <typename T>
T extract(const UT& u)
{
    return u.field[u.position];
}

template <typename T>
UUT duplicate(const UT& u)
{
    return makeUniverseLR(u);
}

template <typename A>
UUUUA duplicate(const UUA& u)
{
    const func<UA(UA)> lCr1 = [](const UA& u1) { return left(u1); };
    const func<UA(UA)> rCr1 = [](const UA& u1) { return right(u1); };
    const func<UUA(UUA)> lCr2 = [](const UUA& u1) { return left(u1); };
    const func<UUA(UUA)> rCr2 = [](const UUA& u1) { return right(u1); };

    const func<UUA(UUA)> lFmapped1 = [=](const UUA& uux) { return fmap(lCr1, uux); };
    const func<UUA(UUA)> rFmapped1 = [=](const UUA& uux) { return fmap(rCr1, uux); };
    const func<UUUA(UUUA)> lFmapped2 = [=](const UUUA& uuux) { return fmap(lCr2, uuux); };
    const func<UUUA(UUUA)> rFmapped2 = [=](const UUUA& uuux) { return fmap(rCr2, uuux); };

    UUUA  shifted1 = makeUniverse(lFmapped1, rFmapped1, u);
    UUUUA shifted2 = makeUniverse(lFmapped2, rFmapped2, shifted1);

    return shifted2;
}

template <typename A, typename B>
UB extend(
    const func<B(UA)>& f,
    const UA& u)
{
    auto duplicated = duplicate(u);
    return fmap(f, duplicated);
}

template <typename A, typename B>
UUB extend(
    const func<B(UUA)>& f,
    const UUA& uu)
{
    UUUUA duplicated = duplicate(uu);
    return fmap(f, duplicated);
}

template <typename A, typename B>
UB stepWith(
    const func<B(UA)>& f,
    const UA& u)
{
    return extend(f, u);
}

template <typename A, typename B>
UUB stepWith(
    const func<B(UUA)>& f,
    const UUA& uu)
{
    return extend(f, uu);
}

} // namespace cmlife


#endif // UNIVERSE_H
