QT -= gui
TARGET = qtcsv
TEMPLATE = lib

!msvc {
    # flags for gcc-like compiler
    CONFIG += warn_on
    QMAKE_CXXFLAGS_WARN_ON += -Werror -Wformat=2 -Wuninitialized -Winit-self \
            -Wmissing-include-dirs -Wswitch-enum -Wundef -Wpointer-arith \
            -Wdisabled-optimization -Wcast-align -Wcast-qual
}

DEFINES += QTCSV_LIBRARY
INCLUDEPATH += $$PWD/include/

# DESTDIR specifies where to put the library file
CONFIG(release, debug|release): DESTDIR = $$PWD
CONFIG(debug, debug|release): DESTDIR = $$PWD

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
    # settings for command "make install"
    libheaders.path = /usr/local/include/qtcsv/
    libheaders.files = $$PWD/include/*.h

    target.path = /usr/local/lib
    INSTALLS += target libheaders
}
