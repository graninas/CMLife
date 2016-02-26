#include "tst_po_benchmark.h"

#include <QString>
#include <QtTest>

#include "comonad.h"
#include "universe.h"
#include "utils.h"
#include "pregnancy_oscillator.h"

#include "async_universe.h"
#include "parallel_universe.h"

#include <vector>
#include <string>
#include <functional>
#include <iostream>

#include <QDebug>

using namespace cmlife;

const int HugeCount = 100;

PORow hugeOscillator()
{
    PORow row;
    row.field.resize(HugeCount);
    row.position = 0;

    for (int i = 0; i < HugeCount; i = i + 5)
        row.field[i] = Pregnant;

    return row;
}

POBenchmarkTest::POBenchmarkTest()
{
}

void POBenchmarkTest::stepPOHugeParBenchmarkTest()
{
    std::function<Cell(PORow)> rule = pregnancyOscillatorRule();
    PORow r1 = hugeOscillator();

    QBENCHMARK {
        auto r2 = stepWithPar(rule, r1);
        QVERIFY(r2.field.size() == HugeCount);
    }
}

void POBenchmarkTest::stepPOHugeBenchmarkTest()
{
    std::function<Cell(PORow)> rule = pregnancyOscillatorRule();
    PORow r1 = hugeOscillator();

    QBENCHMARK {
        auto r2 = stepWith(rule, r1);
        QVERIFY(r2.field.size() == HugeCount);
    }
}

