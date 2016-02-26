#ifndef PAR_H
#define PAR_H

#include <vector>
#include <functional>
#include <algorithm>
#include <future>

#include "functor.h"

namespace cmlife
{

template <typename A, typename B>
std::function<std::future<B>(A)> par(
    const std::function<B(A)>& f)
{
    return [=](const A& a)
    {
        return std::async(std::launch::async,
            [=]() { return f(a); }
        );
    };
}

// Tip: this is monadic join!!
template <typename B>
std::future<std::vector<B>> joinPars(
    std::vector<std::future<B>>& pars)
{
    return std::async(std::launch::async, [&]() // N.B., future requires modification so the & is here.
    {
        std::vector<B> bs;
        bs.reserve(pars.size());

        for (auto& it : pars)
            bs.push_back(it.get());

        return bs;
    });
}

/* A boosted version for the vector (uses reserve()). */
template <typename A, typename B, template <class ...> class Container = std::vector>
std::vector<B> mapPar(
    const std::function<B(A)>& f,
    const std::vector<A>& va)
{
    std::vector<std::future<B>> pars;
    pars.reserve(va.size());
    std::transform(va.begin(), va.end(), std::back_inserter(pars), par(f));
    std::future<std::vector<B>> pRes = joinPars(pars);
    return pRes.get();
}

template <typename A, typename B, template <class ...> class Container>
Container<B> mapPar(
    const std::function<B(A)>& f,
    const Container<A>& va)
{
    Container<std::future<B>> pars = fp::map(par(f), va);
    std::future<Container<B>> pRes = joinPars(pars);
    return pRes.get();
}

template <typename T> UT fmapPar(
    const std::function<T(T)>& f,
    const UT& u)
{
    UT newU;
    newU.position = u.position;
    newU.field = mapPar(f, u.field);
    return newU;
}

} // namespace cmlife

#endif // PAR_H
