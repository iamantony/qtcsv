#include "include/writer.h"

#include <limits>

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QCoreApplication>
#include <QDebug>

#include "include/abstractdata.h"
#include "filechecker.h"
#include "sources/contentiterator.h"

using namespace QtCSV;

class TempFileHandler
{
public:
    explicit TempFileHandler(const QString &filePath) : m_filePath(filePath) {}
    ~TempFileHandler()
    {
        QFile::remove(m_filePath);
    }

private:
    QString m_filePath;
};

// Write data to csv-file
// @input:
// - filePath - string with absolute path to csv-file
// - data - not empty AbstractData object that contains information that should
// be written to csv-file
// - separator - string or character that separate values in a row
// - mode - write mode of the file
// - header - strings that will be written at the beginning of the file in
// one line. separator will be used as delimiter character.
// - footer - strings that will be written at the end of the file in
// one line. separator will be used as delimiter character.
// @output:
// - bool - True if data was written to the file, otherwise False
bool Writer::write(const QString &filePath,
                   const AbstractData &data,
                   const QString &separator,
                   const WriteMode &mode,
                   const QStringList &header,
                   const QStringList &footer)
{
    if ( true == filePath.isEmpty() || true == data.isEmpty() )
    {
        qDebug() << __FUNCTION__ << "Error - invalid arguments";
        return false;
    }

    if ( false == CheckFile(filePath) )
    {
        qDebug() << __FUNCTION__ << "Error - wrong file path/name:" << filePath;
        return false;
    }

    ContentIterator content(data, separator, header, footer);

    bool result = false;
    switch (mode)
    {
        case APPEND:
            result = appendToFile(filePath, content);
            break;
        case REWRITE:
        default:
            result = overwriteFile(filePath, content);
    }

    return result;
}

// Append information to the file
// @input:
// - filePath - string with absolute path to csv-file
// - content - not empty handler of content for csv-file
// @output:
// - bool - True if data was appended to the file, otherwise False
bool Writer::appendToFile(const QString &filePath,
                          ContentIterator &content)
{
    if ( true == filePath.isEmpty() || true == content.isEmpty() )
    {
        qDebug() << __FUNCTION__ << "Error - invalid arguments";
        return false;
    }

    while( content.hasNext() )
    {
        QFile csvFile(filePath);
        if ( false == csvFile.open(QIODevice::Append | QIODevice::Text) )
        {
            qDebug() << __FUNCTION__ << "Error - can't open file:" <<
                        csvFile.fileName();
            return false;
        }

        QTextStream stream(&csvFile);
        stream << content.getNext();
        stream.flush();
        csvFile.close();
    }

    return true;
}

// Overwrite file with new information
// @input:
// - filePath - string with absolute path to csv-file
// - content - not empty handler of content for csv-file
// @output:
// - bool - True if file was overwritten with new data, otherwise False
bool Writer::overwriteFile(const QString &filePath,
                           ContentIterator &content)
{
    // Create temporary file object
    QString tempFileName = getTempFileName();
    if ( tempFileName.isEmpty() )
    {
        qDebug() << __FUNCTION__ <<
                    "Error - failed to create unique name for temp file";
        return false;
    }

    TempFileHandler handler(tempFileName);

    // Write information to temporary file
    if ( false == appendToFile(tempFileName, content) )
    {
        return false;
    }

    // Remove "old" file if it exists
    if ( true == QFile::exists(filePath) && false == QFile::remove(filePath) )
    {
        qDebug() << __FUNCTION__ << "Error - failed to remove file" << filePath;
        return false;
    }

    // Copy "new" file (temporary file) to the destination path (replace
    // "old" file)
    if ( false == QFile::copy(tempFileName, filePath))
    {
        qDebug() << __FUNCTION__ <<
                    "Error - failed to copy temp file to" << filePath;
        return false;
    }

    return true;
}

QString Writer::getTempFileName()
{
    QString nameTemplate = QDir::tempPath() + "/qtcsv_" +
                QString::number(QCoreApplication::applicationPid()) + "_%1.csv";

    QString name;
    for (int counter = 0; counter < std::numeric_limits<int>::max(); ++counter)
    {
        name = nameTemplate.arg(QString::number(qrand()));
        if ( false == QFile::exists(name) )
        {
            break;
        }
    }

    return name;
}
