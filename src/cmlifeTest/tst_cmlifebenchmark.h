#ifndef TST_CMLIFEBENCHMARK_H
#define TST_CMLIFEBENCHMARK_H

#include <QObject>

class CMLifeBenchmarkTest : public QObject
{
    Q_OBJECT

public:
    CMLifeBenchmarkTest();

private Q_SLOTS:

    void stepLifeBenchmarkTest();
    void stepLifeAsyncBenchmarkTest();

    void stepLifeHugeBenchmarkTest();
    void stepLifeHugeAsyncBenchmarkTest();
    void stepLifeHugeParBenchmarkTest();
};

#endif // TST_CMLIFEBENCHMARK_H
