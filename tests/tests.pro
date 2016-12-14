QT += testlib
QT -= gui

TARGET = tst_tests
CONFIG   += console testcase
CONFIG   -= app_bundle

TEMPLATE = app

unix|win32: {
    CONFIG(release, debug|release): LIBS += -L$$PWD/../libs/release -lqtcsv
    CONFIG(debug, debug|release): LIBS += -L$$PWD/../libs/debug -lqtcsv
}

INCLUDEPATH += $$PWD/../include

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
