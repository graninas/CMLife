#include "tst_cmlifebenchmark.h"

#include <QString>
#include <QtTest>

#include "comonad.h"
#include "universe.h"
#include "utils.h"
#include "life.h"

#include "async_universe.h"
#include "parallel_universe.h"

#include "test_data.h"

#include <vector>
#include <string>
#include <functional>
#include <iostream>

#include <QDebug>

using namespace cmlife;

CMLifeBenchmarkTest::CMLifeBenchmarkTest()
{
}

void CMLifeBenchmarkTest::stepLifeBenchmarkTest()
{
/*
    auto rule = lifeRule();
    LifeField l1 = fromVector2(gliderShifted1());

    QBENCHMARK {
        LifeField l2 = stepWith(rule, l1);
        LifeField l3 = stepWith(rule, l2);
        LifeField l4 = stepWith(rule, l3);

        QVERIFY(toVector2(l4) == gliderShifted4());
    }
*/
}

void CMLifeBenchmarkTest::stepLifeAsyncBenchmarkTest()
{
/*
    auto rule = lifeRule();
    LifeField l1 = fromVector2(gliderShifted1());
    QBENCHMARK {
        std::future<LifeField> f1 = async(l1);
        std::future<LifeField> f2 = stepWithAsync(rule, f1);
        std::future<LifeField> f3 = stepWithAsync(rule, f2);
        std::future<LifeField> f4 = stepWithAsync(rule, f3);

        LifeField l4 = f4.get();
        QVERIFY(toVector2(l4) == gliderShifted4());
    }
*/
}

void CMLifeBenchmarkTest::stepLifeHugeBenchmarkTest()
{
    auto rule = lifeRule();
    LifeField l1 = fromVector2(gliderLifeHuge());

    QBENCHMARK {
        LifeField l2 = stepWith(rule, l1);
        QVERIFY(l2.size() == HugeSize);
    }
}

void CMLifeBenchmarkTest::stepLifeHugeParBenchmarkTest()
{
/*
 *     auto rule = lifeRule();
    LifeField l1 = fromVector2(gliderLifeHuge());

    QBENCHMARK {
        LifeField l2 = stepWith2Par(rule, l1);
        QVERIFY(l2.size() == HugeSize);
    }
    */
}

void CMLifeBenchmarkTest::stepLifeHugeAsyncBenchmarkTest()
{
/*
    auto rule = lifeRule();
    LifeField l1 = fromVector2(gliderLifeHuge());
    QBENCHMARK {
        std::future<LifeField> f1 = async(l1);
        std::future<LifeField> f2 = stepWithAsync(rule, f1);
        std::future<LifeField> f3 = stepWithAsync(rule, f2);
        std::future<LifeField> f4 = stepWithAsync(rule, f3);

        LifeField l4 = f4.get();
        QVERIFY(l4.size() == HugeSize);
    }
    */
}
