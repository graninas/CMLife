#ifndef FUNCTOR_H
#define FUNCTOR_H

// TODO: move this to functional_core.

#include <functional>
#include <vector>
#include <algorithm>

namespace cmlife
{

// TODO: don't want use std::transform.
template <typename A, typename B>
std::vector<B> mapVector(
    const std::function<B(A)>& mapper,
    const std::vector<A>& va)
{
    std::vector<B> res;
    res.reserve(va.size());
    std::transform(va.begin(), va.end(), std::back_inserter(res), mapper);
    return res;
}


} // namespace cmlife



#endif // FUNCTOR_H
