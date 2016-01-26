#ifndef LIFE_H
#define LIFE_H

#include <functor.h>
#include <universe.h>

#include <algorithm>

namespace cmlife {

typedef char Cell;

// Tip: If we replace Cell to int, will be type mismatch (it's good).
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

std::vector<Cell> getNeighbours8(const LifeField& field)
{
    std::vector<LifeRow> rows = {
        left(extract(field)),
        right(extract(field)),
        extract(up(field)),
        left(extract(up(field))),
        right(extract(up(field))),
        extract(down(field)),
        left(extract(down(field))),
        right(extract(down(field)))
    };

    const std::function<Cell(LifeRow)> mapper = [](const LifeRow& row) { return value(row); };
    return mapVector(mapper, rows);
}

std::function<Cell(LifeField)> lifeRule =
    [](const LifeField& field)
{
    auto curCell = extract(field);
    auto ns = getNeighbours8(field);

    auto aliveCnt = std::accumulate(ns.begin(), ns.end(), 0,
        [](Cell s, Cell c) { return c == 0 ? s : s+1;});

    switch (aliveCnt) {
    case 2: return extract(curCell);
    case 3: return AliveCell;
    }
    return DeadCell;
};


}

#endif // LIFE_H
