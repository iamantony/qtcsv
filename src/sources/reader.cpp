#include "include/reader.h"

#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "include/abstractdata.h"
#include "filechecker.h"

using namespace QtCSV;

class ReaderPrivate
{
public:
    // Check if file path and separator are valid
    static bool checkParams(const QString& filePath,
                            const QString& separator);
};

// Check if file path and separator are valid
// @input:
// - filePath - string with absolute path to csv-file
// - separator - string or character that separate values in a row
// @output:
// - bool - True if file path and separator are valid, otherwise False
bool ReaderPrivate::checkParams(const QString& filePath,
                                const QString& separator)
{
    if ( filePath.isEmpty() || separator.isEmpty() )
    {
        qDebug() << __FUNCTION__  <<
                    "Error - invalid file path and/or separator";
        return false;
    }

    if ( false == CheckFile(filePath) )
    {
        qDebug() << __FUNCTION__  << "Error - wrong file path/name:" <<
                    filePath;
        return false;
    }

    return true;
}

// Read csv-file and save it's data as strings to QList<QStringList>
// @input:
// - filePath - string with absolute path to csv-file
// - separator - string or character that separate values in a row
// - codec - pointer to codec object that would be used for file reading
// @output:
// - QList<QStringList> - list of values (as strings) from csv-file. If case of
// error will return empty QList<QStringList>.
QList<QStringList> Reader::readToList(const QString &filePath,
                                      const QString &separator,
                                      QTextCodec* codec)
{
    if ( false == ReaderPrivate::checkParams(filePath, separator) )
    {
        return QList<QStringList>();
    }

    QFile csvFile(filePath);
    if ( false == csvFile.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        qDebug() << __FUNCTION__  << "Error - can't open file:" << filePath;
        return QList<QStringList>();
    }

    QList<QStringList> data;
    QTextStream stream(&csvFile);
    stream.setCodec(codec);
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
// - codec - pointer to codec object that would be used for file reading
// @output:
// - bool - True if file was successfully read, otherwise False
bool Reader::readToData(const QString &filePath,
                        AbstractData &data,
                        const QString &separator,
                        QTextCodec* codec)
{
    if ( false == ReaderPrivate::checkParams(filePath, separator) )
    {
        return false;
    }

    QFile csvFile(filePath);
    if ( false == csvFile.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        qDebug() << __FUNCTION__  << "Error - can't open file:" << filePath;
        return false;
    }

    QTextStream stream(&csvFile);
    stream.setCodec(codec);
    while ( false == stream.atEnd() )
    {
        QString line = stream.readLine();
        data.addRow( line.split(separator) );
    }

    csvFile.close();

    return true;
}
