#include "include/reader.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "abstractdata.h"
#include "filechecker.h"

using namespace QtCSV;

// Read csv-file and save it's data as strings to QList<QStringList>
// @input:
// - filePath - string with absolute path to csv-file
// - separator - string or character that separate values in a row
// @output:
// - QList<QStringList> - list of values (as strings) from csv-file. If case of
// error will return empty QList<QStringList>.
QList<QStringList> Reader::readToList(const QString &filePath,
                                      const QString &separator)
{
    if ( filePath.isEmpty() || separator.isEmpty() )
    {
        qDebug() << __func__ << "Error - invalid arguments";
        return QList<QStringList>();
    }

    if ( false == CheckFile(filePath) )
    {
        qDebug() << __func__ << "Error - wrong file path/name:" << filePath;
        return QList<QStringList>();
    }

    QFile csvFile(filePath);
    if ( false == csvFile.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        qDebug() << __func__ << "Error - can't open file:" << filePath;
        return QList<QStringList>();
    }

    QTextStream stream(&csvFile);
    QList<QStringList> data;
    while ( false == stream.atEnd() )
    {
        QString line = stream.readLine();
        data << line.split(separator);
    }

    csvFile.close();

    return data;
}

// Read csv-file and save it's data to AbstractData-based container
// class
// @input:
// - filePath - string with absolute path to csv-file
// - data - AbstractData object where all file content will be saved
// - separator - string or character that separate values in a row
// @output:
// - bool - True if file was successfully read, otherwise False
bool Reader::readToData(const QString &filePath,
                        AbstractData &data,
                        const QString &separator)
{
    if ( filePath.isEmpty() || separator.isEmpty() )
    {
        qDebug() << __func__ << "Error - invalid arguments";
        return false;
    }

    if ( false == CheckFile(filePath) )
    {
        qDebug() << __func__ << "Error - wrong file path/name:" << filePath;
        return false;
    }

    QFile csvFile(filePath);
    if ( false == csvFile.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        qDebug() << __func__ << "Error - can't open file:" << filePath;
        return false;
    }

    QTextStream stream(&csvFile);
    while ( false == stream.atEnd() )
    {
        QString line = stream.readLine();
        data.addRow( line.split(separator) );
    }

    csvFile.close();

    return true;
}
