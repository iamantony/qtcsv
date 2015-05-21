#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T10:40:44
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_tests
CONFIG   += console testcase
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../src/include
LIBS += -L../src/ -lqtcsv
DEFINES += SRCDIR=\\\"$$PWD/\\\"

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
