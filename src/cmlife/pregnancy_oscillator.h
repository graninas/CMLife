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

bool isAorP(Cell a);
bool isA(Cell a);
bool isD(Cell a);
bool isP(Cell a);


std::function<Cell(PORow)> pregnancyOscillatorRule();

} // namespace cmlife

#endif // PREGNANCY_OSCILLATOR_H
