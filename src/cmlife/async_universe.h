#ifndef ASYNC_UNIVERSE_H
#define ASYNC_UNIVERSE_H

#include "universe.h"

#include <future>

namespace cmlife
{

#define FUUUUT std::future<UUUUT>
#define FUUUT std::future<UUUT>
#define FUUT std::future<UUT>
#define FUT std::future<UT>
#define FT std::future<T>

template <typename T> FUUT extend2Async(
    FUUT& fuut,
    const func<T(UUT)>& mapExtr)
{
    return std::async(std::launch::async, [&]() // DANGER!!
    {
        fuut.wait();
        auto uut = fuut.get();
        return extend2(uut, mapExtr);
    });
}

template <typename T> FUUT stepWithAsync(
    const func<T(UUT)>& mapExtr,
    FUUT& fuut)
{
    return extend2Async(fuut, mapExtr);
}

template <typename T> FUUT
   async(const UUT& uut)
{
    return std::async(std::launch::async, [=]() { return uut; });
}

} // namespace cmlife

#endif // ASYNC_UNIVERSE_H
