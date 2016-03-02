QT -= core gui

TARGET = cmlife
TEMPLATE = lib
CONFIG += staticlib

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    life.cpp \
    pregnancy_oscillator.cpp

HEADERS += \
    universe.h \
    parallel_universe.h \
    async_universe.h \
    pregnancy_oscillator.h \
    universe_utils.h \
    game_of_life.h

OTHER_FILES += \
    cmlife.pri

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include($$PWD/../../lib/cpp_functional_core/cpp_functional_core.pri)
include($$PWD/../../lib/cpp_monads/cpp_monads.pri)
include($$PWD/../../lib/cpp_lenses/cpp_lenses.pri)
