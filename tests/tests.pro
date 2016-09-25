QT += testlib
QT -= gui

TARGET = tst_tests
CONFIG   += console testcase
CONFIG   -= app_bundle

TEMPLATE = app

unix|win32: LIBS += -L$$PWD/../src/ -lqtcsv
INCLUDEPATH += $$PWD/../src/include
DEPENDPATH += $$PWD/../src

win32 {
    DESTDIR = $$PWD
}

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
