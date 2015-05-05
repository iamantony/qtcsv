#ifndef QCSVWRITER_H
#define QCSVWRITER_H

#include <QString>
#include <QStringList>

#include "qtcsv_global.h"

namespace QtCSV
{
    class AbstractData;

    class QTCSVSHARED_EXPORT Writer
    {
    public:
        enum class WriteMode
        {
            REWRITE = 0,
            APPEND
        };

        // Write data to .csv file
        static bool write(const QString &filePath,
                          const AbstractData &data,
                          const QString &separator = ",",
                          const WriteMode &mode = WriteMode::REWRITE,
                          const QStringList &header = QStringList(),
                          const QStringList &footer = QStringList());

    private:
        // Get QIODevice mode
        static QIODevice::OpenMode GetMode(const WriteMode &mode);
    };
}

#endif // QCSVWRITER_H
