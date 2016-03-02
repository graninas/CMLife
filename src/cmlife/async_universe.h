#ifndef ASYNC_UNIVERSE_H
#define ASYNC_UNIVERSE_H

#include "universe.h"

#include <future>

namespace cmlife
{

#define FUUUUA std::future<UUUUA>
#define FUUUA std::future<UUUA>
#define FUUA std::future<UUA>
#define FUA std::future<UA>
#define FA std::future<A>
#define FUUUUB std::future<UUUUB>
#define FUUUB std::future<UUUB>
#define FUUB std::future<UUB>
#define FUB std::future<UB>
#define FB std::future<B>

template <typename A, typename B>
FUUB extend2Async(
    const func<B(UUA)>& f,
    FUUA& fuu)
{
    return std::async(std::launch::async, [&]()
    {
        fuu.wait();
        auto uu = fuu.get();
        return extend(f, uu);
    });
}

template <typename A, typename B>
FUUB stepWithAsync(
    const func<B(UUA)>& f,
    FUUA& fuu)
{
    return extend2Async(f, fuu);
}

template <typename A>
FUUA async(const UUA& uu)
{
    return std::async(std::launch::async, [=]() { return uu; });
}

} // namespace cmlife

#endif // ASYNC_UNIVERSE_H
