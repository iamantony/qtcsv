#include "testwriter.h"

#include <QDir>
#include <QFile>
#include <QDebug>

#include "writer.h"
#include "reader.h"
#include "stringdata.h"
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
                                              QtCSV::Writer::WriteMode::APPEND);

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
                                            QtCSV::Writer::WriteMode::REWRITE,
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
                                            QtCSV::Writer::WriteMode::REWRITE,
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
                                            QtCSV::Writer::WriteMode::REWRITE,
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

QString TestWriter::getFilePath() const
{
    return QDir::currentPath() + "/test-file.csv";
}
