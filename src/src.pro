#-------------------------------------------------
#
# Project created by QtCreator 2015-03-22T14:07:29
#
#-------------------------------------------------

QT       -= gui

TARGET = qtcsv
TEMPLATE = lib

QMAKE_CXXFLAGS += -std=c++0x
CONFIG += warn_on
QMAKE_CXXFLAGS_WARN_ON += -Werror -Wformat=2 -Wuninitialized -Winit-self -Wmissing-include-dirs -Wswitch-enum \
		-Wundef -Wpointer-arith -Wdisabled-optimization -Wcast-align -Wcast-qual

DEFINES += QTCSV_LIBRARY

SOURCES += qcsvdata.cpp \
    qcsvwriter.cpp

HEADERS += qcsvdata.h \
    qtcsv_global.h \
    qcsvwriter.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
