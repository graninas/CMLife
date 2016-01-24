#ifndef LIFE_H
#define LIFE_H

#include <universe.h>

#include <algorithm>

namespace cmlife {


typedef char Cell;

// Tip: If we replace Cell to int, will be type mismatch (it's good).
typedef Universe<Cell> U;
typedef Universe<U> U2;

typedef U LifeRow;
typedef U2 LifeField;

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
    return 0; // TODO
};


std::vector<Cell> getNeighbours(const LifeField& field)
{
    return {
        //extract and toLeft,
        //extract and toRight
        //value(toLeft(extract(field)))
    };
}


std::function<Cell(LifeField)> lifeRule =
    [](const LifeField& field)
{
    auto curCell = extract(field);
    auto neighbours = getNeighbours(field);
    auto aliveNeighbours = std::accumulate(neighbours.begin(), neighbours.end(), 0,
        [](Cell c, int cnt)
        {
            return 0; // TODO
        });

    return 0;  // TODO
};


}

#endif // LIFE_H
