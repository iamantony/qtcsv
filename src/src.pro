QT -= gui

TARGET = qtcsv
TEMPLATE = lib

CONFIG += warn_on
QMAKE_CXXFLAGS_WARN_ON += -Werror -Wformat=2 -Wuninitialized -Winit-self \
        -Wmissing-include-dirs -Wswitch-enum -Wundef -Wpointer-arith \
        -Wdisabled-optimization -Wcast-align -Wcast-qual

DEFINES += QTCSV_LIBRARY
INCLUDEPATH += ./include

SOURCES += \
    sources/writer.cpp \
    sources/variantdata.cpp \
    sources/stringdata.cpp \
    sources/reader.cpp

HEADERS += \
    include/qtcsv_global.h \
    include/writer.h \
    include/variantdata.h \
    include/stringdata.h \
    include/reader.h \
    include/abstractdata.h \
    sources/filechecker.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
