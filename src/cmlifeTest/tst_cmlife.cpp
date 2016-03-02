#include "tst_cmlife.h"

#include <QString>
#include <QtTest>

#include "universe.h"
#include "universe_utils.h"
#include "game_of_life.h"
#include "async_universe.h"
#include "parallel_universe.h"

#include "test_data.h"

#include <vector>
#include <string>
#include <functional>
#include <iostream>

#include <QDebug>

using namespace cmlife;

CMLifeTest::CMLifeTest()
{
}

void printField(const LifeField& life)
{
    std::cout << "\n";
    for (int i = 0; i < life.size(); ++i)
    {
        std::cout << "\n";
        for (int j = 0; j < life.field[i].size(); ++j)
        {
            std::cout << (life.field[i].field[j] ? "1" : "0");
        }
    }
    std::cout << "\n";
}

void CMLifeTest::makeUniverseTest()
{
    U2 u = makeUniverseLR(testUniverse());

    QVERIFY(u.size() == 10);
    for (int i = 0; i < u.size(); ++i)
    {
        QVERIFY(u.field[i].position == i);
        QVERIFY(u.field[i].size() == 10);
    }
}

void CMLifeTest::universeComonadTest()
{
    U u = testUniverse();

    U u2 = extract(duplicate(u));
    QVERIFY(u2.field == u.field);
    QVERIFY(u2.position == u.position);

    const std::function<std::string(Universe<Cell>)> mappingExtractor =
        [=](const Universe<Cell>& u){
            return std::to_string(extract(u));
        };

    std::string extracted = extract(extend(mappingExtractor, u));
    QVERIFY(extracted == mappingExtractor(u));

    auto extended = extend(extractLife, u);
    QVERIFY(extended.field == u.field);
    QVERIFY(extended.position == u.position);
}

void CMLifeTest::fromVector2Test()
{
    const auto gl = glider();
    U2 u = fromVector2(gl);

    QVERIFY(u.field.size() == 3);
    for (int i = 0; i < u.size(); ++i)
    {
        QVERIFY(u.field[i].position == 0);
        QVERIFY(u.field[i].size() == 3);
        QVERIFY(u.field[i].field == gl[i]);
    }
}

void CMLifeTest::getNeighbours8_1Test()
{
    LifeField l = gliderLife();
    std::vector<Cell> ns = getNeighbours8(l);
    auto alive = std::accumulate(ns.begin(), ns.end(), 0,
        [](Cell s, Cell c) { return c == 0 ? s : s+1;});
    QVERIFY(ns.size() == 8);
    QVERIFY(alive == 4);
}

void CMLifeTest::getNeighbours8_2Test()
{
    LifeField l = fromVector2(gliderShifted1());
    std::vector<Cell> ns = getNeighbours8(l);
    auto alive = std::accumulate(ns.begin(), ns.end(), 0,
        [](Cell s, Cell c) { return c == 0 ? s : s+1;});
    QVERIFY(ns.size() == 8);
    QVERIFY(alive == 1);
}

void CMLifeTest::stepLifeTest()
{
    auto rule = lifeRule();
    LifeField l1 = fromVector2(gliderShifted1());
    LifeField l2 = stepWith(rule, l1);
    LifeField l3 = stepWith(rule, l2);
    LifeField l4 = stepWith(rule, l3);

//    printField(l1);
//    printField(l2);
//    printField(l3);
//    printField(l4);

    QVERIFY(!l1.field.empty());
    auto rowSize = l1.field[0].size();

    QVERIFY(l2.size() == l1.size());
    for (int i = 0; i < l2.size(); ++i)
    {
        QVERIFY(l2.field[i].size() == rowSize);
    }

    QVERIFY(toVector2(l1) == gliderShifted1());
    QVERIFY(toVector2(l2) == gliderShifted2());
    QVERIFY(toVector2(l3) == gliderShifted3());
    QVERIFY(toVector2(l4) == gliderShifted4());
}

void CMLifeTest::stepLifeAsyncWrapTest()
{
    std::future<LifeField> f1 = async(fromVector2(gliderShifted1()));

    LifeField l1 = f1.get();
    printField(l1);

    QVERIFY(toVector2(l1) == gliderShifted1());
}

void CMLifeTest::stepLifeAsyncSingleTest()
{
    auto rule = lifeRule();
    std::future<LifeField> f1 = async(fromVector2(gliderShifted1()));
    std::future<LifeField> f2 = stepWithAsync(rule, f1);

    LifeField l2 = f2.get();
    printField(l2);

    QVERIFY(toVector2(l2) == gliderShifted2());
}

void CMLifeTest::stepLifeAsyncTest()
{
    auto rule = lifeRule();
    std::future<LifeField> f1 = async(fromVector2(gliderShifted1()));
    std::future<LifeField> f2 = stepWithAsync(rule, f1);
    std::future<LifeField> f3 = stepWithAsync(rule, f2);
    std::future<LifeField> f4 = stepWithAsync(rule, f3);

    // Can't get value from f1, f2, f3: deattached future.
    LifeField l4 = f4.get();
    printField(l4);

    QVERIFY(toVector2(l4) == gliderShifted4());
}

