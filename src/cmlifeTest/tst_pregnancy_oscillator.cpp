#include "tst_pregnancy_oscillator.h"

#include <QDebug>
#include <QString>
#include <QtTest>

#include "comonad.h"
#include "universe.h"
#include "utils.h"
#include "pregnancy_oscillator.h"

#include <vector>
#include <string>
#include <functional>
#include <iostream>

using namespace cmlife;

PregnancyOscillatorTest::PregnancyOscillatorTest()
{
}

void printField(const PORow& row)
{
    std::cout << "\n";
    for (int j = 0; j < row.size(); ++j)
    {
        std::cout << (row.field[j] == 0 ? "0" : (row.field[j] == 1 ? "1" : "P"));
    }
}

void PregnancyOscillatorTest::po1Test()
{
    std::function<Cell(PORow)> rule = pregnancyOscillatorRule();

    PORow r1;
    r1.position = 0;
    r1.field = {0, 0, 0, 0, 0, 0, 0};

    PORow r2 = stepWith(rule, r1);
    PORow r3 = stepWith(rule, r2);
    PORow r4 = stepWith(rule, r3);
    PORow r5 = stepWith(rule, r4);

    //printField(r1);
    //printField(r2);
    //printField(r3);
    //printField(r4);
    //printField(r5);
}

void PregnancyOscillatorTest::po2Test()
{
    std::function<Cell(PORow)> rule = pregnancyOscillatorRule();

    PORow r0;
    r0.position = 0;
    r0.field = {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0};

    printField(r0);
    for(uint i = 0; i < 8; ++i)
    {
        PORow r = stepWith(rule, r0);
        printField(r0);
        r0 = r;
    }
    std::cout << "\n";
}

void PregnancyOscillatorTest::po3Test()
{
    std::function<Cell(PORow)> rule = pregnancyOscillatorRule();

    PORow r0;
    r0.position = 0;
    r0.field = {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0};

    printField(r0);
    for(uint i = 0; i < 20; ++i)
    {
        PORow r = stepWith(rule, r0);
        printField(r);
        r0 = r;
    }

    std::cout << "\n";
}

//QTEST_APPLESS_MAIN(CMLifeTest)
//#include "tst_cmlife.moc"
