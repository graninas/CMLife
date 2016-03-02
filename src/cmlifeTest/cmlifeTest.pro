
QT       += testlib
QT       -= gui

TARGET = tst_cmlifetest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    tst_cmlife.h \
    tst_cmlifebenchmark.h \
    test_data.h \
    tst_pregnancy_oscillator.h \
    tst_po_benchmark.h

SOURCES += \
    ..\cmlife\life.cpp \
    ..\cmlife\pregnancy_oscillator.cpp \
    tst_cmlife.cpp \
    main.cpp \
    tst_cmlifebenchmark.cpp \
    test_data.cpp \
    tst_pregnancy_oscillator.cpp \
    tst_po_benchmark.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"


include($$PWD/../../lib/cpp_functional_core/cpp_functional_core.pri)
include($$PWD/../../lib/cpp_monads/cpp_monads.pri)
include($$PWD/../../lib/cpp_lenses/cpp_lenses.pri)

include($$PWD/../../src/cmlife/cmlife.pri)
