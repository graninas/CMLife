#ifndef TST_PO_BENCHMARK_H
#define TST_PO_BENCHMARK_H

#include <QObject>

class POBenchmarkTest : public QObject
{
    Q_OBJECT

public:
    POBenchmarkTest();

private Q_SLOTS:

    void stepPOHugeParBenchmarkTest();
    void stepPOHugeBenchmarkTest();
};

#endif // TST_PO_BENCHMARK_H
