#ifndef COMONAD_H
#define COMONAD_H

#include "universe.h"

namespace cmlife {

template <typename T> Universe<Universe<T>> stepWith(
        const Universe<Universe<T>>& u,
        const std::function<T(Universe<Universe<T>>)>& rule)
{
    return u;
}

} // namespace cmlife

#endif // COMONAD_H
