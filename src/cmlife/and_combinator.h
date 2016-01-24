#ifndef ANDCOMBINATOR_H
#define ANDCOMBINATOR_H

#include "identity.h"

#include <functional>

namespace cmlife
{

namespace // anonymous
{

struct AndProxy
{
public:
    template<typename T>
    T operator () (T a) const { return a; }
} andProxy;

template <typename L1, typename L2>
LS<Lens<L1, L2>> operator<(const Lens<L1, L2>& l, const AndProxy&)
{
    return LS<Lens<L1, L2>>(l);
}

template <typename ST>
ST operator<(const ST& st, const AndProxy&)
{
    return st;
}

template <typename ST, typename L>
typename ST::template reroll_type<L> operator>(const ST& st, const L& l)
{
    return st.reroll(l);
}

} // namespace anonymous

#define and < andProxy >


} // namespace cmlife

#endif // ANDCOMBINATOR_H
