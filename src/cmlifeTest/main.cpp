
#include <QTest>

#include <tst_cmlife.h>
#include <tst_cmlifebenchmark.h>
#include <tst_pregnancy_oscillator.h>
#include <tst_po_benchmark.h>

int main(int argc, char *argv[])
{
    CMLifeTest tc1;
    int result1 = QTest::qExec(&tc1, argc, argv);
    //int result1 = 0;

    PregnancyOscillatorTest tc2;
    int result2 = QTest::qExec(&tc2, argc, argv);
    //int result2 = 0;

    CMLifeBenchmarkTest tc4;
    int result4 = QTest::qExec(&tc4, argc, argv);
    //int result4 = 0;

    POBenchmarkTest tc3;
    int result3 = QTest::qExec(&tc3, argc, argv);
    //int result3 = 0;

    return result1 & result2 & result3 & result4; // It's a known issue
}

