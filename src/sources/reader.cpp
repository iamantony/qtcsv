#include "include/reader.h"

#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "include/abstractdata.h"
#include "sources/filechecker.h"
#include "sources/symbols.h"

using namespace QtCSV;

class ElementInfo;

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

    static bool readNew(const QString& filePath,
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
                                     const QString& textDelimeter,
                                     bool& rowEnded);

    static QStringList splitElementsNew(const QString& line,
                                        const QString& separator,
                                        const QString& textDelimeter,
                                        ElementInfo& elemInfo);

    // Remove text delimeter symbols
    static QStringList removeTextDelimeters(const QStringList& elements,
                                            const QString& textDelimeter);

    // Get two text delimeter symbols
    static QString getDoubleTextDelimiter(const QString& textDelimiter);
};

struct ElementInfo
{
    bool isEnded = true;
    bool startedWithTD = false;
    int numberOfTD = 0;
    // use only if startedWithTD is True
    int numberOfDoubleTD = 0;
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

    QStringList row;
    bool rowEnded = true;
    while ( false == stream.atEnd() )
    {
        QString line = stream.readLine();
        QStringList elements = ReaderPrivate::splitElements(
                  line, separator, textDelimeter, rowEnded);
        if (rowEnded)
        {
            if (row.isEmpty())
            {
                list << elements;
            }
            else
            {
                if (false == elements.isEmpty())
                {
                    row.last().append(elements.takeFirst());
                    row << elements;
                }

                list << row;
                row.clear();
            }
        }
        else
        {
            if (false == elements.isEmpty())
            {
                if (false == row.isEmpty())
                {
                    row.last().append(elements.takeFirst());
                }

                row << elements;
            }
        }
    }

    csvFile.close();

    if (false == rowEnded && false == row.isEmpty())
    {
        list << row;
    }

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
                                         const QString& textDelimeter,
                                         bool& rowEnded)
{
    // If separator is empty, return whole line. Can't work in this
    // conditions!
    if (separator.isEmpty())
    {
        rowEnded = true;
        return (QStringList() << line);
    }

    if (line.isEmpty())
    {
        // If previous row was ended, then return empty QStringList.
        // Otherwise return list that contains one element - new line symbols
        if (rowEnded)
        {
            return QStringList();
        }
        else
        {
            return (QStringList() << LF);
        }
    }

    const QStringList elements = line.split(separator);

    // If rowEnded is True, then we process a new row.
    // If rowEnded is False, then:
    // - the last element of the previous row(s) started with text delimeter
    // symbol
    // - information at the beginning of the row would be appended to the end
    // of the last element of the previous row
    // - the last element of the previous row should contain LF symbol (new
    // line)
    QStringList result;
    if (false == rowEnded)
    {
        result << LF;
    }

    const QString doubleTextDelim = getDoubleTextDelimiter(textDelimeter);
    for (int i = 0; i < elements.size(); ++i)
    {
        const bool startsWith = elements.at(i).startsWith(textDelimeter);
        const bool endsWith = elements.at(i).endsWith(textDelimeter);
        if (rowEnded)
        {
            // If rowEnded is True, then this element will be the new element.
            // If it is ends and starts with text delimiter or just not starts
            // with text delimiter, then add this element to the result list
            // as is.
            if ( (false == startsWith) ||
                 (startsWith && endsWith) )
            {
                result << elements.at(i);
                continue;
            }

            // If current elements only starts with text delimiter, then
            // next elements in a row should be appended to this element till
            // the element that ends with text delimiter. Because it is
            // possible, that we will not find in this line such 'end' element,
            // we set flag rowEnded to false.
            rowEnded = false;
            QString str = elements.at(i);
            for (int j = i + 1; j < elements.size(); ++j, ++i)
            {
                str += separator + elements.at(j);

                const bool elemEndsWithTD =
                        elements.at(j).endsWith(textDelimeter);
                const bool elemEndsWithDoubleTD =
                        elements.at(j).endsWith(doubleTextDelim);
                if (elemEndsWithTD && false == elemEndsWithDoubleTD)
                {
                    // We found 'end' element. Set up new i value and set
                    // rowEnded to true.
                    ++i;
                    rowEnded = true;
                    break;
                }
            }

            result << str;
        }
        else
        {
            QString strToAdd = elements.at(i);
            if (0 < i)
            {
                strToAdd.prepend(separator);
            }

            result.last().append(strToAdd);

            const bool endsWithDoubleTD =
                    elements.at(i).endsWith(doubleTextDelim);
            if (endsWith && false == endsWithDoubleTD)
            {
                rowEnded = true;
            }
        }
    }

    return removeTextDelimeters(result, textDelimeter);
}

bool ReaderPrivate::readNew(const QString& filePath,
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

    QStringList row;
    ElementInfo elemInfo;
    while ( false == stream.atEnd() )
    {
        QString line = stream.readLine();
        QStringList elements = ReaderPrivate::splitElementsNew(
                  line, separator, textDelimeter, elemInfo);
        if (elemInfo.isEnded)
        {
            if (row.isEmpty())
            {
                list << elements;
            }
            else
            {
                if (false == elements.isEmpty())
                {
                    row.last().append(elements.takeFirst());
                    row << elements;
                }

                list << row;
                row.clear();
            }
        }
        else
        {
            if (false == elements.isEmpty())
            {
                if (false == row.isEmpty())
                {
                    row.last().append(elements.takeFirst());
                }

                row << elements;
            }
        }
    }

    csvFile.close();

    if (false == elemInfo.isEnded && false == row.isEmpty())
    {
        list << row;
    }

    return true;
}

QStringList ReaderPrivate::splitElementsNew(const QString& line,
                                            const QString& separator,
                                            const QString& textDelimeter,
                                            ElementInfo& elemInfo)
{
    // If separator is empty, return whole line. Can't work in this
    // conditions!
    if (separator.isEmpty())
    {
        elemInfo.isEnded = true;
        return (QStringList() << line);
    }

    if (line.isEmpty())
    {
        // If previous row was ended, then return empty QStringList.
        // Otherwise return list that contains one element - new line symbols
        if (elemInfo.isEnded)
        {
            return QStringList();
        }
        else
        {
            return (QStringList() << LF);
        }
    }

    QStringList result;
    const QString doubleTextDelim = getDoubleTextDelimiter(textDelimeter);
    int pos = 0;
    while(pos < line.size())
    {
        if (false == elemInfo.isEnded)
        {
            result << LF;

            int separatorPos = line.indexOf(separator, pos);
            int delimeterPos = line.indexOf(textDelimeter, pos);
            int doubleDelimPos = line.indexOf(doubleTextDelim, pos);
            if (elemInfo.startedWithTD)
            {
                if (elemInfo.numberOfDoubleTD == 0)
                {
                    if (delimeterPos < doubleDelimPos || doubleDelimPos < 0)
                    {
                        result.last().append(/*chars in line from pos to separatorPos*/);
                        pos = separatorPos;
                        elemInfo.isEnded = true;
                    }
                    else
                    {

                    }
                }
                else
                {

                }
            }
            else
            {

            }


        }

        int separatorPos = line.indexOf(separator);
        int delimeterPos = line.indexOf(textDelimeter);
    }

}

// Remove text delimeter symbols
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
    const QString doubleTextDelim = getDoubleTextDelimiter(textDelimeter);
    for (int i = 0; i < elements.size(); ++i)
    {
        QString str = elements.at(i);

        // If string starts and ends with text delimiter symbols, then remove
        // them
//        if (str.startsWith(textDelimeter) &&
//                str.endsWith(textDelimeter))
//        {
//            str.chop(textDelimeter.size());
//            str.remove(0, textDelimeter.size());
//        }

        if (str.startsWith(textDelimeter))
        {
            str.remove(0, textDelimeter.size());
        }

        if (str.endsWith(textDelimeter))
        {
            str.chop(textDelimeter.size());
        }

        // Also replace double text delimiter with one text delimiter symbol
        str.replace(doubleTextDelim, textDelimeter);
        result << str;
    }

    return result;
}

// Get two text delimeter symbols
// @input:
// - textDelimiter - string
// @output:
// - QString - string that contains two text delimiter symbols
QString ReaderPrivate::getDoubleTextDelimiter(const QString& textDelimiter)
{
    return textDelimiter + textDelimiter;
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
