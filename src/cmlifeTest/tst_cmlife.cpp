#include <QString>
#include <QtTest>

#include <universe.h>
#include <comonad.h>
#include <utils.h>
#include <life.h>

#include <vector>
#include <functional>

#include <QDebug>

using namespace cmlife;

class CMLifeTest : public QObject
{
    Q_OBJECT

public:
    CMLifeTest();

private Q_SLOTS:
    void makeUniverseTest();
    void fromVector2Test();
    void stepLifeTest();
};

CMLifeTest::CMLifeTest()
{
}


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
        {0, 1, 1},
        {1, 0, 0},
        {0, 1, 0}
    };
}

void CMLifeTest::makeUniverseTest()
{
    std::function<U(U)> leftGen = [](const U& iu) {
        return left(iu);
        };

    std::function<U(U)> rightGen = [](const U& iu) {
        return right(iu);
        };

    U2 u = makeUniverse(leftGen, rightGen, testUniverse());

    QVERIFY(u.size() == 10);
    for (int i = 0; i < u.size(); ++i)
    {
        QVERIFY(u.field[i].position == i);
        QVERIFY(u.field[i].size() == 10);
    }
}

void CMLifeTest::fromVector2Test()
{
    U2 u = fromVector2(glider());

    QVERIFY(u.field.size() == 3);
    for (int i = 0; i < u.size(); ++i)
    {
        QVERIFY(u.field[i].position == 0);
        QVERIFY(u.field[i].size() == 3);
        QVERIFY(u.field[i].field == glider()[i]);
    }
}

void CMLifeTest::stepLifeTest()
{
    LifeField l1 = fromVector2(glider());
    LifeField l2 = stepWith(l1, lifeRule);
}

QTEST_APPLESS_MAIN(CMLifeTest)

#include "tst_cmlife.moc"
