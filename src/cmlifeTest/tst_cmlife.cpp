#include <QString>
#include <QtTest>

#include <vector>

#include <universe.h>
#include <functional>

#include <QDebug>

using namespace cmlife;

typedef Universe<int> U;
typedef Universe<U> U2;

class CMLifeTest : public QObject
{
    Q_OBJECT

public:
    CMLifeTest();

private Q_SLOTS:
    void makeUniverseTest();
};

CMLifeTest::CMLifeTest()
{
}

void CMLifeTest::makeUniverseTest()
{
    U u;
    u.position = 0;
    u.field = {1,2,3,4,5,6,7,8,9,10};

    std::function<U(U)> leftGen = [](const U& iu) {
        return left(iu);
        };

    std::function<U(U)> rightGen = [](const U& iu) {
        return right(iu);
        };

    U2 u2 = makeUniverse(leftGen, rightGen, u);

    for (int i = 0; i < u2.size(); ++i)
    {
        QVERIFY(u2.field[i].position == i);
    }
}

QTEST_APPLESS_MAIN(CMLifeTest)

#include "tst_cmlife.moc"
