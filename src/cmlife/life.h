#ifndef LIFE_H
#define LIFE_H

#include <universe.h>

namespace cmlife {


typedef char Cell;

// Tip: If we replace Cell to int, will be type mismatch (it's good).
typedef Universe<Cell> U;
typedef Universe<U> U2;

typedef U2 LifeField;


std::function<Cell(LifeField)> lifeRule = [](const LifeField& field)
{
    return 2;
};


}

#endif // LIFE_H
