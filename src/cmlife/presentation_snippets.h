#ifndef PRESENTATION_SNIPPETS_H
#define PRESENTATION_SNIPPETS_H

#include "universe.h"
#include "pregnancy_oscillator.h"

using namespace cmlife;


CARow left(const CARow& u) {
   CARow newU { u.field, u.position - 1 };
   if (u.position == 0)
       newU.position = u.size() - 1;
   return newU;
}

CARow right(const CARow& u) {
    CARow newU { u.field, u.position + 1 };
    if (u.position == u.size() - 1)
        newU.position = 0;
    return newU;
}


Cell extract(const CARow& u) {
    return u.field[u.position];
}

CARow u;

auto current = extract(u);

auto rValue = extract(right(u));
auto rrValue = extract(right(right(u)));

auto lValue = extract(left(u));
auto llValue = extract(left(left(u)));


Cell rule(const CARow& row) {

    // extract l, ll, cur, r, rr here

    if (isA(l) && isA(r) && !isAorP(cur))
        return Pregnant;

    // ... more rules here

    return Dead;
}

template <typename T>
T rule (const Universe<T>& u) {}

template <typename T>
Universe<T> left (const Universe<T>& u) {}

template <typename T>
Universe<T> right (const Universe<T>& u) {}

template <typename T>
Universe<T> extend (
   std::function<T(Universe<T>)> f,
   Universe<T> u) {}

template <typename T>
Universe<Universe<T>> duplicate (Universe<T> u) {}

CARow left (const CARow& u)
{}
CARow right (const CARow& u)
{}
Cell extract(const CARow& u)
{}
Cell pregnancyOscillatorRule(const CARow& row)
{}

Universe<T> left (const Universe<T>& u)
{}
Universe<T> right (const Universe<T>& u)
{}
T extract (const Universe<T>& u)
{}
T someRule (const Universe<T>& row)
{}

Universe<Universe<Cell>>
duplicate (const Universe<Cell>& u)
{}

Universe<Cell> extend(
    const std::function<Cell(Universe<Cell>)>& f,
    const Universe<Cell>& u)
{}

// For shortness and presentability
#define UT Universe<T>
#define UUT Universe<Universe<T>>
#define ShiftFunction std::function<UT(UT)>

const func<UT(UT)> leftCreator =
   [](const UT& u) {return left(u); };

const func<UT(UT)> rightCreator =
   [](const UT& u) {return right(u); };

template <typename T> UUT duplicate(const UT& u) {
   return makeUniverse(leftCreator, rightCreator, u);
}


template <typename T> UUT makeUniverse(
    const func<UT(UT)>& leftCreator,
    const func<UT(UT)>& rightCreator,
    const UT& u) {

    auto lefts = tailOfGen(u.position, leftCreator, u);
    auto rights = tailOfGen(u.size() - u.position - 1, rightCreator, u);

    std::vector<UT> all;
    all.swap(lefts);
    all.push_back(u);
    all.insert(all.end(), rights.begin(), rights.end());

    return { std::move(all), u.position };
}

template <typename T> T extract(const UT& u)
{
    return u.field[u.position];
}

template <typename T, typename B>
UB extend(
    const func<B(UT)>& f,
    const UT& u)
{
    UUT duplicated = duplicate(u);
    std::vector<B> mapped = fp::map(f, duplicated.field);
    return { std::move(mapped), u.position };
}

template<typename A, typename B,
         template <class ...> class Container>
Container<B> map(
    const std::function<B(A)>& f,
    const Container<A>& va)
{
    Container<B> vb;
    std::transform(va.begin(), va.end(), std::back_inserter(vb), f);
    return vb;
}


Universe<Universe<Cell>>
duplicate (const Universe<Cell>& u) {

    const ShiftFunction leftCreator =
        [](const UT& u1) { return left(u1); };

    const ShiftFunction rightCreator =
        [](const UT& u1) { return right(u1); };

    std::vector<UT> all = std::vector<UT>();
    all.reserve(u.size());

    auto lefts = tailOfGen(u.position, leftCreator, u);
    auto rights = tailOfGen(u.size() - u.position - 1, rightCreator, u);

    all.insert(all.end(), lefts.begin(), lefts.end());
    all.push_back(u);
    all.insert(all.end(), rights.begin(), rights.end());

    UUT newU { all, u.position };
    return newU;
}


UB extend(
    const std::function<B(UT)>& mappingExtractor,
    const UT& u)
{
    auto duplicated = duplicate(u);
    auto mapped = fp::map(mappingExtractor, duplicated.field);
    UB newU {mapped, u.position};
    return newU;
}


typedef Universe<Cell> LifeRow;
typedef Universe<LifeRow> LifeField;

#endif // PRESENTATION_SNIPPETS_H
