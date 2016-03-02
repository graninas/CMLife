win32:      CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../src/cmlife/release/ -lcmlife
else:win32: CONFIG(debug, debug|release):   LIBS += -L$$OUT_PWD/../../src/cmlife/debug/ -lcmlife
else:unix:                                  LIBS += -L$$OUT_PWD/../../src/cmlife/ -lcmlife

INCLUDEPATH += $$PWD/../../src/cmlife
DEPENDPATH  += $$PWD/../../src/cmlife

win32-g++:             CONFIG(release, debug|release):  PRE_TARGETDEPS += $$OUT_PWD/../../src/cmlife/release/libcmlife.a
else:win32-g++:        CONFIG(debug, debug|release):    PRE_TARGETDEPS += $$OUT_PWD/../../src/cmlife/debug/libcmlife.a
else:win32:!win32-g++: CONFIG(release, debug|release):  PRE_TARGETDEPS += $$OUT_PWD/../../src/cmlife/release/libcmlife.lib
else:win32:!win32-g++: CONFIG(debug, debug|release):    PRE_TARGETDEPS += $$OUT_PWD/../../src/cmlife/debug/libcmlife.lib
else:unix:                                              PRE_TARGETDEPS += $$OUT_PWD/../../src/cmlife/libcmlife.a
