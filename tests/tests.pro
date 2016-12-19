QT += testlib
QT -= gui

TARGET = qtcsv_tests
CONFIG += console testcase
CONFIG -= app_bundle

TEMPLATE = app

CONFIG(release, debug|release): LIBS += -L$$PWD/../ -lqtcsv
CONFIG(debug, debug|release): LIBS += -L$$PWD/../ -lqtcsv

CONFIG(release, debug|release): DESTDIR = $$PWD/../
CONFIG(debug, debug|release): DESTDIR = $$PWD/../

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
