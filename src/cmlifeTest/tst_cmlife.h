#ifndef TST_CMLIFE_H
#define TST_CMLIFE_H

#include <QObject>

class CMLifeTest : public QObject
{
    Q_OBJECT

public:
    CMLifeTest();

private Q_SLOTS:
    void makeUniverseTest();
    void universeComonadTest();
    void universe2ComonadTest();

    void fromVector2Test();
    void getNeighbours8_1Test();
    void getNeighbours8_2Test();

    void stepLifeTest();
    void stepLifeAsyncWrapTest();
    void stepLifeAsyncSingleTest();
    void stepLifeAsyncTest();
};

#endif // TST_CMLIFE_H
