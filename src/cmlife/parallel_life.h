#ifndef PARALLEL_LIFE_H
#define PARALLEL_LIFE_H

#include "universe.h"
#include "parallel_universe.h"
#include "life.h"

#include <future>

namespace cmlife
{

/*
std::function<Cell(LifeField)>
 lifeRulePar =
 [](std::future<LifeField>& fieldF)
{

    return std::async(std::launch::async, [&]()
    {
        fieldF.wait(); // Should be function!
        LifeField field = fieldF.get(); // Can't use purely!!! Should be auto res = fieldF.get();
        return lifeRule(field);
    });

};

*/

} // namespace cmlife


#endif // PARALLEL_LIFE_H
