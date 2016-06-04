QT += testlib
QT -= gui

TARGET = tst_tests
CONFIG   += console testcase
CONFIG   -= app_bundle

TEMPLATE = app

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/release/ -lqtcsv
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug/ -lqtcsv
else:unix: LIBS += -L$$OUT_PWD/../src/ -lqtcsv

INCLUDEPATH += $$PWD/../src/include
DEPENDPATH += $$PWD/../src/

SOURCES += \
    tst_testmain.cpp \
    teststringdata.cpp \
    testvariantdata.cpp \
    testreader.cpp \
    testwriter.cpp

HEADERS += \
    teststringdata.h \
    testvariantdata.h \
    testreader.h \
    testwriter.h
