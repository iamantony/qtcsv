#ifndef QTCSVFILECHECKER_H
#define QTCSVFILECHECKER_H

#include <QString>
#include <QFileInfo>
#include <QDebug>

namespace QtCSV
{
    // Check if path to csv file is valid
    // @input:
    // - filePath - string with absolute path to csv-file
    // @output:
    // - bool - True if file is OK, else False
    inline bool CheckFile(const QString& filePath)
    {
        QFileInfo fileInfo(filePath);
        if ( fileInfo.isAbsolute() && fileInfo.isFile() )
        {
            if ( "csv" != fileInfo.suffix() )
            {
                qDebug() << __FUNCTION__  <<
                            "Warning - file suffix is not .csv";
            }

            return true;
        }

        return false;
    }
}

#endif // QTCSVFILECHECKER_H
