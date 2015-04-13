#ifndef FILECHECKER_H
#define FILECHECKER_H

#include <QString>
#include <QFileInfo>

namespace QtCSV
{
    // Check if path to csv file is valid
    // @input:
    // - filePath - string with absolute path to csv-file
    // @output:
    // - bool - True if file is OK, else False
    inline bool CheckFile(const QString &filePath)
    {
        QFileInfo fileInfo(filePath);
        if ( fileInfo.isAbsolute() && "csv" == fileInfo.completeSuffix() )
        {
            return true;
        }

        return false;
    }
}

#endif // FILECHECKER_H
