#ifndef QCSVWRITER_H
#define QCSVWRITER_H

#include <QString>
#include <QStringList>

#include "qtcsv_global.h"

namespace QtCSV
{
    class AbstractData;
    class ContentIterator;

    // Writer is a file-writer class that works with csv-files.
    // As a source of information it requires AbstractData-based container
    // class object.
    // It support different write methods:
    // - WriteMode::REWRITE - if file exist, it content will be rewritten
    // - WriteMode::APPEND - if file exist, new information will be appended
    // to the end of file.
    // Also it can add header and footer to a file.
    class QTCSVSHARED_EXPORT Writer
    {
    public:
        enum WriteMode
        {
            REWRITE = 0,
            APPEND
        };

        // Write data to csv-file
        static bool write(const QString &filePath,
                          const AbstractData &data,
                          const QString &separator = ",",
                          const WriteMode &mode = REWRITE,
                          const QStringList &header = QStringList(),
                          const QStringList &footer = QStringList());

        private:
            // Append information to the file
            static bool appendToFile(const QString &filePath,
                                     ContentIterator &content);

            // Overwrite file with new information
            static bool overwriteFile(const QString &filePath,
                                      ContentIterator &content);

            static QString getTempFileName();
    };
}

#endif // QCSVWRITER_H
