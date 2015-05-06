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
QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = app

INCLUDEPATH += ../src/include
LIBS += -L../src/ -lqtcsv

SOURCES += \
    tst_testmain.cpp \
    teststringdata.cpp \
    testvariantdata.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    teststringdata.h \
    testvariantdata.h
