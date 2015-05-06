#ifndef QTCSVREADER_H
#define QTCSVREADER_H

#include <QList>
#include <QStringList>

#include "qtcsv_global.h"

namespace QtCSV
{
    class AbstractData;

    // Reader class is a special file reader that work with csv-files. All it
    // needs are an absolute path to the csv-file and a character that is
    // used as values separator in this csv-file.
    // It can save information to QList<QStringList>, where each
    // QStringList contains values of one row.
    // Or it can save information to AbstractData-based container class, using
    // virtual function addRow(QStringList&).
    class QTCSVSHARED_EXPORT Reader
    {
    public:
        // Read csv-file and save it's data as strings to QList<QStringList>
        static QList<QStringList> readToList(const QString &filePath,
                                             const QString &separator = ",");

        // Read csv-file and save it's data to AbstractData-based container
        // class
        static bool readToData(const QString &filePath,
                               AbstractData &data,
                               const QString &separator = ",");
    };
}

#endif // QTCSVREADER_H
