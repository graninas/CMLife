
QT       += testlib
QT       -= gui

TARGET = tst_cmlifetest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11


SOURCES += \
    ..\cmlife\life.cpp \ #this is a temporary hack
    tst_cmlife.cpp \
    main.cpp \
    tst_cmlifebenchmark.cpp \
    test_data.cpp \
    tst_pregnancy_oscillator.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

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

INCLUDEPATH += $$PWD/../../lib/cpp_lenses/cpp_lenses
DEPENDPATH += $$PWD/../../lib/cpp_lenses/cpp_lenses

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_lenses/cpp_lenses/release/libcpp_lenses.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_lenses/cpp_lenses/debug/libcpp_lenses.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_lenses/cpp_lenses/release/cpp_lenses.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_lenses/cpp_lenses/debug/cpp_lenses.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_lenses/cpp_lenses/libcpp_lenses.a


INCLUDEPATH += $$PWD/../../src/cmlife
DEPENDPATH += $$PWD/../../src/cmlife

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/cmlife/release/libcmlife.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/cmlife/debug/libcmlife.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/cmlife/release/libcmlife.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/cmlife/debug/libcmlife.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../src/cmlife/libcmlife.a

HEADERS += \
    tst_cmlife.h \
    tst_cmlifebenchmark.h \
    test_data.h \
    tst_pregnancy_oscillator.h
