#include "testwriter.h"

#include <exception>

#include <QDir>
#include <QFile>
#include <QTime>
#include <QDebug>

#include "writer.h"
#include "reader.h"
#include "variantdata.h"

TestWriter::TestWriter()
{
}

void TestWriter::cleanup()
{
    if ( false == QFile::remove(getFilePath()) )
    {
        qDebug() << "Can't remove file:" << getFilePath();
    }
}

QString TestWriter::getFilePath() const
{
    return QDir::currentPath() + "/test-file.csv";
}

void TestWriter::testWriteInvalidArgs()
{
    QVERIFY2(false == QtCSV::Writer::write(QString(), QtCSV::StringData()),
             "Invalid arguments was accepted");

    QVERIFY2(false == QtCSV::Writer::write(getFilePath(), QtCSV::StringData()),
             "Empty data was accepted");

    QtCSV::StringData strData;
    strData << "one" << "two" << "three";

    QVERIFY2(false == QtCSV::Writer::write(QString(), strData),
             "Empty path was accepted");

    QVERIFY2(false == QtCSV::Writer::write("./some/path.exe", strData),
             "Relative path to exe-file was accepted");

    QVERIFY2(false == QtCSV::Writer::write("./some/path.csv", strData),
             "Relative path to csv-file was accepted");

    QVERIFY2(false == QtCSV::Writer::write(getFilePath() + ".xls", strData),
             "Absolute path to xls-file was accepted");
}

void TestWriter::testWriteFromStringData()
{
    QStringList strList;
    strList << "one" << "two" << "three";

    QtCSV::StringData strData;
    strData.addRow(strList);

    bool writeResult = QtCSV::Writer::write(getFilePath(), strData);
    QVERIFY2(true == writeResult, "Failed to write to file");

    QList<QStringList> data = QtCSV::Reader::readToList(getFilePath());
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");
    QVERIFY2(1 == data.size(), "Wrong number of rows");
    QVERIFY2(strList == data.at(0), "Wrong data");
}

void TestWriter::testWriteFromVariantData()
{
    double expectedValue = 42.12309;
    QVariant firstRow(expectedValue);

    QList<QVariant> secondRow;
    secondRow << QVariant("kkoo") << QVariant(771) << QVariant(3.14);

    QStringList thirdRow;
    thirdRow << "one" << "two" << "three";

    QtCSV::VariantData varData;
    varData.addRow(firstRow);
    varData.addRow(secondRow);
    varData.addRow(thirdRow);

    bool writeResult = QtCSV::Writer::write(getFilePath(), varData);
    QVERIFY2(true == writeResult, "Failed to write to file");

    QList<QStringList> data = QtCSV::Reader::readToList(getFilePath());
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");
    QVERIFY2(3 == data.size(), "Wrong number of rows");
    QVERIFY2(varData.getRowValues(0) == data.at(0),
             "Wrong values in first row");

    QVERIFY2(varData.getRowValues(1) == data.at(1),
             "Wrong values in second row");

    QVERIFY2(varData.getRowValues(2) == data.at(2),
             "Wrong values in third row");
}

void TestWriter::testWriteAppendMode()
{
    QStringList strFirstList;
    strFirstList << "one" << "two" << "three";

    QtCSV::StringData strData;
    strData.addRow(strFirstList);

    bool writeResult = QtCSV::Writer::write(getFilePath(), strData);
    QVERIFY2(true == writeResult, "Failed to write to file");

    QStringList strSecondList;
    strSecondList << "3" << "2" << "1.1";

    QtCSV::StringData newStrData;
    newStrData.addRow(strSecondList);

    bool newWriteResult = QtCSV::Writer::write(getFilePath(),
                                              newStrData,
                                              ",",
                                              QtCSV::Writer::APPEND);

    QVERIFY2(true == newWriteResult, "Failed to write to file");

    QList<QStringList> data = QtCSV::Reader::readToList(getFilePath());
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");
    QVERIFY2(2 == data.size(), "Wrong number of rows");
    QVERIFY2(strFirstList == data.at(0), "Wrong first row data");
    QVERIFY2(strSecondList == data.at(1), "Wrong second row data");
}

void TestWriter::testWriteWithNotDefaultSeparator()
{
    QStringList strList;
    strList << "one" << "two" << "three";

    QtCSV::StringData strData;
    strData.addRow(strList);

    const QString separator("++");
    bool writeResult = QtCSV::Writer::write(getFilePath(), strData, separator);
    QVERIFY2(true == writeResult, "Failed to write to file");

    QList<QStringList> data =
            QtCSV::Reader::readToList(getFilePath(), separator);
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");
    QVERIFY2(1 == data.size(), "Wrong number of rows");
    QVERIFY2(strList == data.at(0), "Wrong data");
}

void TestWriter::testWriteWithHeader()
{
    QStringList header;
    header << "1" << "2";

    QStringList strList;
    strList << "one" << "two" << "three";

    QtCSV::StringData strData;
    strData.addRow(strList);

    bool writeResult = QtCSV::Writer::write(getFilePath(),
                                            strData,
                                            ",",
                                            QtCSV::Writer::REWRITE,
                                            header);

    QVERIFY2(true == writeResult, "Failed to write to file");

    QList<QStringList> data = QtCSV::Reader::readToList(getFilePath());
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");
    QVERIFY2(2 == data.size(), "Wrong number of rows");
    QVERIFY2(header == data.at(0), "Wrong header");
    QVERIFY2(strList == data.at(1), "Wrong data");
}

void TestWriter::testWriteWithFooter()
{
    QStringList footer;
    footer << "Here is a footer";

    QStringList strList;
    strList << "one" << "two" << "three";

    QtCSV::StringData strData;
    strData.addRow(strList);

    bool writeResult = QtCSV::Writer::write(getFilePath(),
                                            strData,
                                            ",",
                                            QtCSV::Writer::REWRITE,
                                            QStringList(),
                                            footer);

    QVERIFY2(true == writeResult, "Failed to write to file");

    QList<QStringList> data = QtCSV::Reader::readToList(getFilePath());
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");
    QVERIFY2(2 == data.size(), "Wrong number of rows");
    QVERIFY2(strList == data.at(0), "Wrong data");
    QVERIFY2(footer == data.at(1), "Wrong footer");
}

void TestWriter::testWriteWithHeaderAndFooter()
{
    QStringList header;
    header << "1" << "2";

    QStringList footer;
    footer << "Here is a footer";

    QStringList strList;
    strList << "one" << "two" << "three";

    QtCSV::StringData strData;
    strData.addRow(strList);

    bool writeResult = QtCSV::Writer::write(getFilePath(),
                                            strData,
                                            ",",
                                            QtCSV::Writer::REWRITE,
                                            header,
                                            footer);

    QVERIFY2(true == writeResult, "Failed to write to file");

    QList<QStringList> data = QtCSV::Reader::readToList(getFilePath());
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");
    QVERIFY2(3 == data.size(), "Wrong number of rows");
    QVERIFY2(header == data.at(0), "Wrong header");
    QVERIFY2(strList == data.at(1), "Wrong data");
    QVERIFY2(footer == data.at(2), "Wrong footer");
}

void TestWriter::testWriteDifferentDataAmount()
{
    int rowsNumber = 10;
    int rowsMultiplier  = 4;
    int rowCycles = 9;
    QTime time;
    for ( int i = 0; i < rowCycles; ++i )
    {
        int symbolsNumber = 10;
        int symbolsMultiplier  = 5;
        int symbolCycles = 4;
        for ( int j = 0; j < symbolCycles; ++j )
        {
            QtCSV::StringData data;
            try
            {
                data = getTestStringData(symbolsNumber, rowsNumber);
            }
            catch (std::exception &e)
            {
                QFAIL("No enough memory to create data object");
            }

            QVERIFY2(false == data.isEmpty(), "Failed to create content");

            bool writeResult = false;
            time.restart();
            try
            {
                writeResult = QtCSV::Writer::write(getFilePath(), data);
            }
            catch (std::exception &e)
            {
                QFAIL("No enough memory to write data to the file");
            }

            qDebug() << "symbols:" << symbolsNumber <<
                        ", rows:" << rowsNumber <<
                        ", time:" << time.elapsed() << "ms";

            QVERIFY2(true == writeResult, "Failed to write to file");

            QList<QStringList> result =
                    QtCSV::Reader::readToList(getFilePath());
            QVERIFY2(false == result.isEmpty(), "Failed to read file content");
            QVERIFY2(data.getNumberOfRows() == result.size(),
                     "Wrong number of rows");

            for ( int k = 0; k < result.size(); ++k )
            {
                QVERIFY2(data.getRowValues(k) == result.at(k),
                         "Original and result data are not the same");
            }

            symbolsNumber *= symbolsMultiplier;
        }

        rowsNumber *= rowsMultiplier;
    }
}

QtCSV::StringData TestWriter::getTestStringData(const int &symbolsInRow,
                                                const int &rowsNumber)
{
    if ( symbolsInRow <= 0 || rowsNumber <= 0 )
    {
        qDebug() << __FUNCTION__ << "Invalid argumnets";
        return QtCSV::StringData();
    }

    QStringList elements;
    elements << "1234567890" << "3.14159265359" << "abcdefgh" <<
                "ijklmnopqrs" << "tuvwxyz" << "ABCDEFGH" << "IJKLMNOPQRS" <<
                "TUVWXYZ" << "some_STRANGE-string=" <<
                "?!\\|/*+.<>@#$%^&(){}[]'`~";

    QStringList rowElements;
    int rowLength = 0;
    int elementIndex = 0;
    while ( rowLength < symbolsInRow )
    {
        if ( elements.size() <= elementIndex )
        {
            elementIndex = 0;
        }

        QString nextElement = elements.at(elementIndex);
        if ( symbolsInRow < rowLength + nextElement.size() )
        {
            nextElement.resize( symbolsInRow - rowLength );
        }

        rowElements << nextElement;
        rowLength += nextElement.size();
        ++elementIndex;
    }

    QtCSV::StringData data;
    for ( int i = 0; i < rowsNumber; ++i )
    {
        data.addRow(rowElements);
    }

    return data;
}
