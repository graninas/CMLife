#include "life.h"

#include <functor.h>
#include <universe.h>

#include <algorithm>

namespace cmlife {

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
    return fp::map(mapper, rows);
}

std::function<Cell(LifeField)> lifeRule()
{
return [](const LifeField& field)
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

}
