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
    utils.h \
    life.h \
    comonad.h \
    and_combinator.h \
    applicative.h \
    parallel_life.h \
    parallel_universe.h \
    par.h \
    async_universe.h \
    pregnancy_oscillator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/cpp_functional_core/release/ -lcpp_functional_core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/cpp_functional_core/debug/ -lcpp_functional_core
else:unix: LIBS += -L$$OUT_PWD/../../lib/cpp_functional_core/ -lcpp_functional_core

INCLUDEPATH += $$PWD/../../lib/cpp_functional_core
DEPENDPATH += $$PWD/../../lib/cpp_functional_core

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_functional_core/release/libcpp_functional_core.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_functional_core/debug/libcpp_functional_core.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_functional_core/release/cpp_functional_core.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_functional_core/debug/cpp_functional_core.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_functional_core/libcpp_functional_core.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/cpp_monads/cpp_monads/release/ -lcpp_monads
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/cpp_monads/cpp_monads/debug/ -lcpp_monads
else:unix: LIBS += -L$$OUT_PWD/../../lib/cpp_monads/cpp_monads/ -lcpp_monads

INCLUDEPATH += $$PWD/../../lib/cpp_monads/cpp_monads
DEPENDPATH += $$PWD/../../lib/cpp_monads/cpp_monads

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_monads/cpp_monads/release/libcpp_monads.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_monads/cpp_monads/debug/libcpp_monads.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_monads/cpp_monads/release/cpp_monads.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_monads/cpp_monads/debug/cpp_monads.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_monads/cpp_monads/libcpp_monads.a
