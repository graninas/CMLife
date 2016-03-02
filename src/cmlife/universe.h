#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "map.h"

#include <vector>
#include <functional>
#include <algorithm>
#include <utility>

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

#define UA Universe<A>
#define UUA Universe<Universe<A>>
#define UUUA Universe<Universe<Universe<A>>>
#define UUUUA Universe<Universe<Universe<Universe<A>>>>
#define UB Universe<B>
#define UUB Universe<Universe<B>>
#define UUUB Universe<Universe<Universe<B>>>
#define UUUUB Universe<Universe<Universe<Universe<B>>>>
#define func function

template <typename A>
struct Universe
{
    std::vector<A> field;
    int position;

    int size() const
    {
        return field.size();
    }
};

template <typename A>
UA left(const UA& u)
{
    UA newU { u.field, u.position - 1 };
    if (u.position == 0)
        newU.position = u.size() - 1;
    return newU;
}

template <typename A>
UA right(const UA& u)
{
    UA newU { u.field, u.position + 1 };
    if (u.position == u.size() - 1)
        newU.position = 0;
    return newU;
}

template <typename A>
std::vector<UA> tailOfGen(
    int count,
    const std::function<UA(UA)>& generator,
    UA item)
{
    std::vector<UA> items;
    items.reserve(count);

    auto it = generator(item);
    for (int i = 0; i < count; ++i)
    {
        items.push_back(it);
        it = generator(it);
    }
    return items;
}

template <typename A>
UUA makeUniverse(
    const func<UA(UA)>& leftCreator,
    const func<UA(UA)>& rightCreator,
    const UA& u)
{
    std::vector<UA> lefts  = tailOfGen(u.position, leftCreator, u);
    std::vector<UA> rights = tailOfGen(u.size() - u.position - 1, rightCreator, u);

    std::vector<UA> all;
    all.reserve(u.size());
    all.insert(all.end(), lefts.begin(), lefts.end());
    all.push_back(u);
    all.insert(all.end(), rights.begin(), rights.end());

    return { std::move(all), u.position };
}

template <typename A>
UUA makeUniverseLR(const UA& u)
{
    const std::function<UA(UA)> leftCr = [](const UA& u1) {return left(u1); };
    const std::function<UA(UA)> rightCr = [](const UA& u1) {return right(u1); };

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

template <typename A>
UA pure(const A& t)
{
    return {{t}, 0};
}

// Comonad implementation

template <typename A>
A extract(const UA& u)
{
    return u.field[u.position];
}

template <typename A>
UUA duplicate(const UA& u)
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
