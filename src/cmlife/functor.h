#ifndef FUNCTOR_H
#define FUNCTOR_H

// TODO: move this to functional_core.

#include <functional>
#include <vector>
#include <algorithm>

namespace cmlife
{

template<typename A, typename B, template <class ...> class Container>
Container<B> map(
    const std::function<B(A)>& mapper,
    const Container<A>& va)
{
    Container<B> vb;
    std::transform(va.begin(), va.end(), std::back_inserter(vb), mapper);
    return vb;
}


} // namespace cmlife



#endif // FUNCTOR_H
