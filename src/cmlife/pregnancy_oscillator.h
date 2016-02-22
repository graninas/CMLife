#ifndef PREGNANCY_OSCILLATOR_H
#define PREGNANCY_OSCILLATOR_H

#include <functor.h>
#include <universe.h>

#include <algorithm>

namespace cmlife {

typedef char Cell;

typedef Universe<Cell> PORow;

const Cell Pregnant = 2;
const Cell Alive    = 1;
const Cell Dead     = 0;

/*
const std::function<Cell(PORow)> value = [](const PORow& row)
{
    return extract(row);
};
*/
bool isAlive(Cell a)
{
    return a == Alive || a == Pregnant;
}

bool isDead(Cell a)
{
    return a == Dead;
}

bool isPregnant(Cell a)
{
    return a == Pregnant;
}

std::function<Cell(PORow)> pregnancyOscillatorRule()
{
return [](const PORow& row)
    {
        auto cur = extract(row);

        auto r = extract(right(row));
        auto l = extract(left(row));
        auto rr = extract(right(right(row)));
        auto ll = extract(left(left(row)));

        if (isAlive(l) && isAlive(r) && isAlive(cur))
            return Dead;

        if (l == Alive && r == Alive && !isAlive(cur))
            return Pregnant;

        if (isPregnant(l) || isPregnant(r) || isPregnant(cur))
            return Alive;

        if (isAlive(r) && isAlive(rr))
            return Alive;

        if (isAlive(l) && isAlive(ll))
            return Alive;

        return Dead;
    };
}

} // namespace cmlife

#endif // PREGNANCY_OSCILLATOR_H
