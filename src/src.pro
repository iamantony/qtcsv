QT -= gui

TARGET = qtcsv
TEMPLATE = lib

equals(QT_MAJOR_VERSION, 4):lessThan(QT_MINOR_VERSION, 8) {
    error("qtcsv library requires Qt 4.8 and higher")
}

equals(QT_MAJOR_VERSION, 4):equals(QT_MINOR_VERSION, 8) {
    QMAKE_CXXFLAGS += -std=c++0x
}

greaterThan(QT_MAJOR_VERSION, 4) {
    CONFIG += c++11
}

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
