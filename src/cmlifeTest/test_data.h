#ifndef TEST_DATA_H
#define TEST_DATA_H

#include <universe.h>
#include <universe_utils.h>
#include <game_of_life.h>

#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <iostream>

cmlife::U testUniverse();

std::vector<std::vector<cmlife::Cell>> glider();

std::vector<std::vector<cmlife::Cell>> oscillator();

std::vector<std::vector<cmlife::Cell>> gliderShifted1();
std::vector<std::vector<cmlife::Cell>> gliderShifted2();
std::vector<std::vector<cmlife::Cell>> gliderShifted3();
std::vector<std::vector<cmlife::Cell>> gliderShifted4();

cmlife::LifeField gliderLife();

const int HugeSize = 100;
std::vector<std::vector<cmlife::Cell>> gliderLifeHuge();

#endif // TEST_DATA_H
