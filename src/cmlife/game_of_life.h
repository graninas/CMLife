#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <algorithm>
#include "universe.h"

namespace cmlife {

typedef char Cell;

typedef Universe<Cell> U;
typedef Universe<U> U2;

typedef U LifeRow;
typedef U2 LifeField;

const Cell AliveCell = 1;
const Cell DeadCell  = 0;

const std::function<LifeField(LifeField)> toLeft =
    [](const LifeField& field)
    {
        return left(field);
    };

const std::function<LifeField(LifeField)> toRight =
    [](const LifeField& field)
    {
        return right(field);
    };

const std::function<LifeField(LifeField)> up = toLeft;
const std::function<LifeField(LifeField)> down = toRight;

const std::function<Cell(Universe<Cell>)> extractLife =
        [](const Universe<Cell>& u) { return extract(u); };
const std::function<Universe<Universe<Cell>>(Universe<Cell>)> duplicateLife =
        [](const Universe<Cell>& u) { return duplicate(u); };

const std::function<Cell(LifeRow)> value = [](const LifeRow& row)
{
    return extract(row);
};

std::vector<Cell> getNeighbours8(const LifeField& field);

std::function<Cell(LifeField)> lifeRule();

}

#endif // GAME_OF_LIFE_H
