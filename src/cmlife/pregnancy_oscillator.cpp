#include "pregnancy_oscillator.h"

namespace cmlife
{

/*
bool isAlive(Aliveness a)
{
    return a == Alive || a == Pregnant;
}


std::function<Aliveness(PORow)> pregnancyOscillatorRule()
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

        if (isAlive(r) && isAlive(rr))
            return Alive;

        if (isAlive(l) && isAlive(ll))
            return Alive;

        return Dead;
    };
}
*/

} // namespace cmlife
