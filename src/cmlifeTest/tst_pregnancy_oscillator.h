#ifndef TST_PREGNANCY_OSCILLATOR_H
#define TST_PREGNANCY_OSCILLATOR_H

#include <QObject>

class PregnancyOscillatorTest : public QObject
{
    Q_OBJECT

public:
    PregnancyOscillatorTest();

private Q_SLOTS:

    void po1Test();
    void po2Test();
    void po3Test();
};

#endif // TST_PREGNANCY_OSCILLATOR_H
