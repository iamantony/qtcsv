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
    // Function that really reads csv-file and save it's data as strings to
    // QList<QStringList>
    static bool read(const QString& filePath,
                     QList<QStringList>& list,
                     const QString& separator,
                     const QString& textDelimeter,
                     QTextCodec* codec);

private:
    // Check if file path and separator are valid
    static bool checkParams(const QString& filePath,
                            const QString& separator);

    // Split string line to elements by separators
    static QStringList splitElements(const QString& line,
                                     const QString& separator,
                                     const QString& textDelimeter);

    // Remove text delimeter symbols from the beginning and the end of the
    // elements
    static QStringList removeTextDelimeters(const QStringList& elements,
                                            const QString& textDelimeter);
};

// Function that really reads csv-file and save it's data as strings to
// QList<QStringList>
// @input:
// - filePath - string with absolute path to csv-file
// - list - refernce to list container where read data will be saved
// - separator - string or character that separate values in a row
// - textDelimeter - string or character that enclose each element in a row
// - codec - pointer to codec object that would be used for file reading
// @output:
// - QList<QStringList> - list of values (as strings) from csv-file. If case of
// error will return empty QList<QStringList>.
bool ReaderPrivate::read(const QString& filePath,
                         QList<QStringList>& list,
                         const QString& separator,
                         const QString& textDelimeter,
                         QTextCodec* codec)
{
    if ( false == checkParams(filePath, separator) )
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
        list << ReaderPrivate::splitElements(line, separator, textDelimeter);
    }

    csvFile.close();

    return true;
}

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

// Split string line to elements by separators
// @input:
// - line - string with data
// - separator - string or character that separate values in a row
// - textDelimeter - string that used as text delimeter
// @output:
// - QStringList - list of elements
QStringList ReaderPrivate::splitElements(const QString& line,
                                         const QString& separator,
                                         const QString& textDelimeter)
{
    if (line.isEmpty() || separator.isEmpty())
    {
        return (QStringList() << QString());
    }

    QStringList elements = line.split(separator);
    if (1 == elements.size() || textDelimeter == separator)
    {
        return removeTextDelimeters(elements, textDelimeter);
    }

    QStringList result;
    for (int i = 0; i < elements.size(); ++i)
    {
        bool startsWith = elements.at(i).startsWith(textDelimeter);
        bool endsWith = elements.at(i).endsWith(textDelimeter);
        if ( (false == startsWith) ||
             (startsWith && endsWith) )
        {
            result << elements.at(i);
            continue;
        }

        QString str = elements.at(i);
        for (int j = i + 1; j < elements.size(); ++j, ++i)
        {
            str += separator + elements.at(j);
            if (elements.at(j).endsWith(textDelimeter))
            {
                ++i;
                break;
            }
        }

        if (false == str.isEmpty())
        {
            result << str;
        }
    }

    return removeTextDelimeters(result, textDelimeter);
}

// Remove text delimeter symbols from the beginning and the end of the elements
// @input:
// - elements - list of string elements
// - textDelimeter - string that delimeter text parts from each other
// @output:
// - QStringList - list of elements
QStringList ReaderPrivate::removeTextDelimeters(const QStringList& elements,
                                                const QString& textDelimeter)
{
    if (elements.isEmpty() || textDelimeter.isEmpty())
    {
        return elements;
    }

    QStringList result;
    for (int i = 0; i < elements.size(); ++i)
    {
        QString str = elements.at(i);
        if (str.startsWith(textDelimeter) &&
                str.endsWith(textDelimeter))
        {
            str.chop(textDelimeter.size());
            str.remove(0, textDelimeter.size());
        }

        result << str;
    }

    return result;
}

// Read csv-file and save it's data as strings to QList<QStringList>
// @input:
// - filePath - string with absolute path to csv-file
// - separator - string or character that separate values in a row
// - textDelimeter - string or character that enclose each element in a row
// - codec - pointer to codec object that would be used for file reading
// @output:
// - QList<QStringList> - list of values (as strings) from csv-file. If case of
// error will return empty QList<QStringList>.
QList<QStringList> Reader::readToList(const QString& filePath,
                                      const QString& separator,
                                      const QString& textDelimeter,
                                      QTextCodec* codec)
{
    QList<QStringList> data;
    ReaderPrivate::read(filePath, data, separator, textDelimeter, codec);

    return data;
}

// Read csv-file and save it's data to AbstractData-based container
// class
// @input:
// - filePath - string with absolute path to csv-file
// - data - AbstractData object where all file content will be saved
// - separator - string or character that separate values in a row
// - textDelimeter - string or character that enclose each element in a row
// - codec - pointer to codec object that would be used for file reading
// @output:
// - bool - True if file was successfully read, otherwise False
bool Reader::readToData(const QString& filePath,
                        AbstractData& data,
                        const QString& separator,
                        const QString& textDelimeter,
                        QTextCodec* codec)
{
    QList<QStringList> list;
    if (false == ReaderPrivate::read(filePath, list, separator, textDelimeter,
                                     codec))
    {
        return false;
    }

    for (int i = 0; i < list.size(); ++i)
    {
        data.addRow( list.at(i) );
    }

    return true;
}
