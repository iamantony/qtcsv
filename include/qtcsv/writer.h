#ifndef QTCSVWRITER_H
#define QTCSVWRITER_H

#include <QString>
#include <QStringList>
#if QT_VERSION >= 0x060000
#include <QStringConverter>
#include <QtCore5Compat/QTextCodec>
#else
#include <QTextCodec>
#endif

#include "qtcsv/qtcsv_global.h"

class QIODevice;

namespace QtCSV
{
    class AbstractData;
    class ContentIterator;

    // Writer is a data-writer class that works with csv-files and IO Devices.
    // As a source of information it requires AbstractData-based container
    // class object.
    //
    // It supports different write methods:
    // - WriteMode::REWRITE - if file exist, it will be rewritten
    // - WriteMode::APPEND - if file exist, new information will be appended
    // to the end of the file.
    //
    // Also you can specify header and footer for your data.
    class QTCSVSHARED_EXPORT Writer
    {
    public:
        enum WriteMode
        {
            REWRITE = 0,
            APPEND
        };

        // Write data to csv-file
        static bool write(const QString& filePath,
                        const AbstractData& data,
                        const QString& separator = QString(","),
                        const QString& textDelimiter = QString("\""),
                        const WriteMode& mode = REWRITE,
                        const QStringList& header = QStringList(),
                        const QStringList& footer = QStringList(),
#if QT_VERSION >= 0x060000
                        QStringConverter::Encoding codec = QStringConverter::Utf8
#else
                        QTextCodec* codec = QTextCodec::codecForName("UTF-8")
#endif
                );

        // Write data to IO Device
        static bool write(QIODevice& ioDevice,
                        const AbstractData& data,
                        const QString& separator = QString(","),
                        const QString& textDelimiter = QString("\""),
                        const QStringList& header = QStringList(),
                        const QStringList& footer = QStringList(),
#if QT_VERSION >= 0x060000
                          QStringConverter::Encoding codec = QStringConverter::Utf8
#else
                          QTextCodec* codec = QTextCodec::codecForName("UTF-8")
#endif
                );
    };
}

#endif // QTCSVWRITER_H
