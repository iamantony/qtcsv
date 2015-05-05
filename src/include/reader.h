#ifndef QTCSVREADER_H
#define QTCSVREADER_H

#include <QList>
#include <QStringList>

#include "qtcsv_global.h"

namespace QtCSV
{
    class AbstractData;

    class QTCSVSHARED_EXPORT Reader
    {
    public:
        // Read .csv file to QList<QStringList>
        static QList<QStringList> readToList(const QString &filePath,
                                             const QString &separator = ",");

        // Read .csv file to AbstractData
        static bool readToData(const QString &filePath,
                               AbstractData &data,
                               const QString &separator = ",");
    };
}

#endif // QTCSVREADER_H
