QT -= gui

TARGET = qtcsv
TEMPLATE = lib

QMAKE_CXXFLAGS += -std=c++0x
CONFIG += warn_on
QMAKE_CXXFLAGS_WARN_ON += -Werror -Wformat=2 -Wuninitialized -Winit-self \
		-Wmissing-include-dirs -Wswitch-enum -Wundef -Wpointer-arith \
		-Wdisabled-optimization -Wcast-align -Wcast-qual

DEFINES += QTCSV_LIBRARY

SOURCES += \
    reader.cpp \
    writer.cpp \
    variantdata.cpp \
    stringdata.cpp

HEADERS += \
    qtcsv_global.h \
	separator.h \
    reader.h \
	writer.h \
    abstractdata.h \
    variantdata.h \
    stringdata.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
