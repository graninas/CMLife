#ifndef PAR_H
#define PAR_H

#include <vector>
#include <functional>
#include <algorithm>
#include <future>

namespace cmlife
{

/*
template <typename A, typename B>
std::function<std::future<B>(A)> par(
    const std::function<B(A)> mapper)
{
    return [=](const A a)
    {
        return std::async(std::launch::async,
            [=]() { return mapper(a); }
        );
    };
}
*/

// Tip: this is monadic join!!
template <typename B>
std::future<std::vector<B>> joinPars(
    std::vector<std::future<B>>& pars)
{
    return std::async(std::launch::async, [&]()
    {
        std::vector<B> bs;
        bs.reserve(pars.size());

        for (auto it = pars.begin(); it != pars.end(); ++it)
        {
            bs.push_back(it->get());
        }

        return bs;
    });
}

template <typename A, typename B>
std::vector<B> mapVectorPar(
    const std::function<B(A)>& mapper,
    const std::vector<A>& va)
{

    const std::function<std::future<B>(A)> pMapper = [&](const A& a)
    {
        return std::async(std::launch::async, [&]()
        {
            return mapper(a);
        });
    };

    std::vector<std::future<B>> pars;
    pars.reserve(va.size());
    std::transform(va.begin(), va.end(), std::back_inserter(pars), pMapper);
    std::future<std::vector<B>> pRes = joinPars(pars);
    return pRes.get();
}

} // namespace cmlife

#endif // PAR_H
