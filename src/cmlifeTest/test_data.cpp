#include "test_data.h"

#include <universe.h>
#include <universe_utils.h>
#include <game_of_life.h>

#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <iostream>

using namespace cmlife;

U testUniverse()
{
    U u;
    u.position = 0;
    u.field = {1,2,3,4,5,6,7,8,9,10};
    return u;
}

std::vector<std::vector<Cell>> glider()
{
    return {
        {1, 1, 1},
        {1, 0, 0},
        {0, 1, 0}
    };
}

std::vector<std::vector<Cell>> oscillator()
{
    return {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
}

std::vector<std::vector<Cell>> gliderShifted1()
{
    return {
        {0,0,0, 0, 0, 0, 0,0,0},
        {0,0,0, 0, 0, 0, 0,0,0},
        {0,0,0, 0, 0, 0, 0,0,0},
        {0,0,0, 1, 1, 1, 0,0,0},
        {0,0,0, 1, 0, 0, 0,0,0},
        {0,0,0, 0, 1, 0, 0,0,0},
        {0,0,0, 0, 0, 0, 0,0,0},
        {0,0,0, 0, 0, 0, 0,1,1},
        {0,0,0, 0, 0, 0, 0,1,1},
    };
}

std::vector<std::vector<Cell>> gliderShifted2()
{
    return {
        {0,0,0, 0, 0, 0, 0,0,0},
        {0,0,0, 0, 0, 0, 0,0,0},
        {0,0,0, 0, 1, 0, 0,0,0},
        {0,0,0, 1, 1, 0, 0,0,0},
        {0,0,0, 1, 0, 1, 0,0,0},
        {0,0,0, 0, 0, 0, 0,0,0},
        {0,0,0, 0, 0, 0, 0,0,0},
        {0,0,0, 0, 0, 0, 0,1,1},
        {0,0,0, 0, 0, 0, 0,1,1},
    };
}

std::vector<std::vector<Cell>> gliderShifted3()
{
    return {
        {0,0,0, 0, 0, 0, 0,0,0},
        {0,0,0, 0, 0, 0, 0,0,0},
        {0,0,0, 1, 1, 0, 0,0,0},
        {0,0,0, 1, 0, 1, 0,0,0},
        {0,0,0, 1, 0, 0, 0,0,0},
        {0,0,0, 0, 0, 0, 0,0,0},
        {0,0,0, 0, 0, 0, 0,0,0},
        {0,0,0, 0, 0, 0, 0,1,1},
        {0,0,0, 0, 0, 0, 0,1,1},
    };
}

std::vector<std::vector<Cell>> gliderShifted4()
{
    return {
        {0,0, 0, 0, 0, 0, 0,0,0},
        {0,0, 0, 0, 0, 0, 0,0,0},
        {0,0, 0, 1, 1, 0, 0,0,0},
        {0,0, 1, 1, 0, 0, 0,0,0},
        {0,0, 0, 0, 1, 0, 0,0,0},
        {0,0, 0, 0, 0, 0, 0,0,0},
        {0,0, 0, 0, 0, 0, 0,0,0},
        {0,0, 0, 0, 0, 0, 0,1,1},
        {0,0, 0, 0, 0, 0, 0,1,1},
    };
}

LifeField gliderLife()
{
    return fromVector2(glider());
}

std::vector<std::vector<Cell>> gliderLifeHuge()
{
    std::vector<std::vector<Cell>> field;
    field.resize(HugeSize);

    for (int i = 0; i < HugeSize; ++i)
    {
        field[i].resize(HugeSize);
        std::fill_n(field[i].begin(), HugeSize, 0);
    }

    const int shift = HugeSize / 2;
    field[shift + 0][shift + 1] = 1;
    field[shift + 0][shift + 2] = 1;
    field[shift + 1][shift + 0] = 1;
    field[shift + 1][shift + 1] = 1;
    field[shift + 2][shift + 2] = 1;

    return field;
}
