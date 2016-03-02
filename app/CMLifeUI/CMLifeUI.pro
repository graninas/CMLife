



QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CMLifeUI
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

FORMS    += cmlifeview.ui

RESOURCES += \
    Icons.qrc

SOURCES += \
    main.cpp \
    cmlifeview.cpp

HEADERS += \
    presentationsnippets.h \
    cmlifeview.h

include($$PWD/../../lib/cpp_functional_core/cpp_functional_core.pri)
include($$PWD/../../lib/cpp_monads/cpp_monads.pri)
include($$PWD/../../lib/cpp_lenses/cpp_lenses.pri)

include($$PWD/../../src/cmlife/cmlife.pri)




