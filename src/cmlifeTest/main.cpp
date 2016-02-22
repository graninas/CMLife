
#include <QTest>

#include <tst_cmlife.h>
#include <tst_cmlifebenchmark.h>
#include <tst_pregnancy_oscillator.h>

int main(int argc, char *argv[])
{
    CMLifeTest tc1;
    int result1 = QTest::qExec(&tc1, argc, argv);

    PregnancyOscillatorTest tc2;
    int result2 = QTest::qExec(&tc2, argc, argv);

    //CMLifeBenchmarkTest tc2;
    //int result2 = QTest::qExec(&tc2, argc, argv);

    return result1 & result2; // It's a known issue
}

