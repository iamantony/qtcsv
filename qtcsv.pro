QT -= gui
TARGET = qtcsv
TEMPLATE = lib

!msvc {
    CONFIG += warn_on
    QMAKE_CXXFLAGS_WARN_ON += -Werror -Wformat=2 -Wuninitialized -Winit-self \
            -Wmissing-include-dirs -Wswitch-enum -Wundef -Wpointer-arith \
            -Wdisabled-optimization -Wcast-align -Wcast-qual
}

DEFINES += QTCSV_LIBRARY
INCLUDEPATH += $$PWD/include/
CONFIG(release, debug|release): DESTDIR = $$PWD/libs/release
CONFIG(debug, debug|release): DESTDIR = $$PWD/libs/debug

SOURCES += \
    sources/writer.cpp \
    sources/variantdata.cpp \
    sources/stringdata.cpp \
    sources/reader.cpp \
    sources/contentiterator.cpp

HEADERS += \
    include/qtcsv/qtcsv_global.h \
    include/qtcsv/writer.h \
    include/qtcsv/variantdata.h \
    include/qtcsv/stringdata.h \
    include/qtcsv/reader.h \
    include/qtcsv/abstractdata.h \
    sources/filechecker.h \
    sources/contentiterator.h \
    sources/symbols.h

unix {
    libheaders.path = /usr/local/include/qtcsv/
    libheaders.files = $$PWD/include/*.h

    target.path = /usr/local/lib
    INSTALLS += target libheaders
}
