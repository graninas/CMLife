#include "pregnancy_oscillator.h"

namespace cmlife
{

bool isAorP(Cell a)
{
    return a == Alive || a == Pregnant;
}

bool isA(Cell a)
{
    return a == Alive;
}

bool isD(Cell a)
{
    return a == Dead;
}

bool isP(Cell a)
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

            if (isAorP(l) && isAorP(r) && isAorP(cur))
                return Dead;

            if (isA(l) && isA(r) && !isAorP(cur))
                return Pregnant;

            if (isP(l) || isP(r) || isP(cur))
                return Alive;

            if (   (isAorP(r) && isAorP(rr))
                || (isAorP(l) && isAorP(ll)))
                return Alive;

            if (isAorP(l) && isAorP(ll))
                return Alive;

            return Dead;
        };
}

} // namespace cmlife
