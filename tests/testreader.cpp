#include "testreader.h"

#include <QDir>

#include "reader.h"
#include "stringdata.h"
#include "variantdata.h"

TestReader::TestReader()
{
}

void TestReader::testReadToListInvalidArgs()
{
    QVERIFY2(QList<QStringList>() ==
                            QtCSV::Reader::readToList(QString(), QString()),
             "Invalid arguments was accepted");

    QVERIFY2(QList<QStringList>() ==
             QtCSV::Reader::readToList(getPathToFileTestComma(), QString()),
             "Invalid arguments was accepted");

    QVERIFY2(QList<QStringList>() == QtCSV::Reader::readToList(QString(), ","),
             "Invalid arguments was accepted");

    QVERIFY2(QList<QStringList>() ==
             QtCSV::Reader::readToList("./some/path.exe", ","),
             "Invalid arguments was accepted");

    QVERIFY2(QList<QStringList>() ==
             QtCSV::Reader::readToList("./some/path.csv", ","),
             "Invalid arguments was accepted");

    QVERIFY2(QList<QStringList>() ==
             QtCSV::Reader::readToList(getPathToFileTestComma() + ".md5", ","),
             "Invalid arguments was accepted");
}

void TestReader::testReadToDataInvalidArgs()
{
    QtCSV::StringData data;

    QVERIFY2(false == QtCSV::Reader::readToData(QString(), data, QString()),
             "Invalid arguments was accepted");

    QVERIFY2(false == QtCSV::Reader::readToData(getPathToFileTestComma(), data,
                                                QString()),
             "Invalid arguments was accepted");

    QVERIFY2(false == QtCSV::Reader::readToData(QString(), data, ","),
             "Invalid arguments was accepted");

    QVERIFY2(false == QtCSV::Reader::readToData("./some/path.exe", data, ","),
             "Invalid arguments was accepted");

    QVERIFY2(false == QtCSV::Reader::readToData("./some/path.csv", data,","),
             "Invalid arguments was accepted");

    QVERIFY2(false == QtCSV::Reader::readToData(
                 getPathToFileTestComma() + ".md5", data,","),
             "Invalid arguments was accepted");
}

void TestReader::testReadFileWithCommas()
{
    const QString path = getPathToFileTestComma();
    QList<QStringList> data = QtCSV::Reader::readToList(path);

    QVERIFY2(false == data.isEmpty(), "Failed to read file content");
    QVERIFY2(5 == data.size(), "Wrong number of rows");

    QStringList expectedFirstRow;
    expectedFirstRow << "one" << "two" << "three";

    QStringList expectedSecondRow;
    expectedSecondRow << "one_element";

    QStringList expectedThirdRow;
    expectedThirdRow << "1" << "2" << "3";

    QStringList expectedFourthRow;
    expectedFourthRow << "";

    QStringList expectedFifthRow;
    expectedFifthRow << "3.14";

    QVERIFY2(expectedFirstRow == data.at(0), "Wrong first row");
    QVERIFY2(expectedSecondRow == data.at(1), "Wrong second row");
    QVERIFY2(expectedThirdRow == data.at(2), "Wrong third row");
    QVERIFY2(expectedFourthRow == data.at(3), "Wrong fourth row");
    QVERIFY2(expectedFifthRow == data.at(4), "Wrong fifth row");
}

void TestReader::testReadFileWithCommasToStringData()
{
    const QString path = getPathToFileTestComma();
    QtCSV::StringData strData;
    bool readResult = QtCSV::Reader::readToData(path, strData);
    QVERIFY2(true == readResult, "Failed to read file content");

    QVERIFY2(false == strData.isEmpty(), "StringData is empty");
    QVERIFY2(5 == strData.rowCount(), "Wrong number of rows");

    QStringList expectedFirstRow;
    expectedFirstRow << "one" << "two" << "three";

    QStringList expectedSecondRow;
    expectedSecondRow << "one_element";

    QStringList expectedThirdRow;
    expectedThirdRow << "1" << "2" << "3";

    QStringList expectedFourthRow;
    expectedFourthRow << "";

    QStringList expectedFifthRow;
    expectedFifthRow << "3.14";

    QVERIFY2(expectedFirstRow == strData.rowValues(0), "Wrong first row");
    QVERIFY2(expectedSecondRow == strData.rowValues(1), "Wrong second row");
    QVERIFY2(expectedThirdRow == strData.rowValues(2), "Wrong third row");
    QVERIFY2(expectedFourthRow == strData.rowValues(3), "Wrong fourth row");
    QVERIFY2(expectedFifthRow == strData.rowValues(4), "Wrong fifth row");
}

void TestReader::testReadFileWithCommasToVariantData()
{
    const QString path = getPathToFileTestComma();
    QtCSV::VariantData varData;
    bool readResult = QtCSV::Reader::readToData(path, varData);
    QVERIFY2(true == readResult, "Failed to read file content");

    QVERIFY2(false == varData.isEmpty(), "StringData is empty");
    QVERIFY2(5 == varData.rowCount(), "Wrong number of rows");

    QStringList expectedFirstRow;
    expectedFirstRow << "one" << "two" << "three";

    QStringList expectedSecondRow;
    expectedSecondRow << "one_element";

    QStringList expectedThirdRow;
    expectedThirdRow << "1" << "2" << "3";

    QStringList expectedFourthRow;
    expectedFourthRow << "";

    QStringList expectedFifthRow;
    expectedFifthRow << "3.14";

    QVERIFY2(expectedFirstRow == varData.rowValues(0), "Wrong first row");
    QVERIFY2(expectedSecondRow == varData.rowValues(1), "Wrong second row");
    QVERIFY2(expectedThirdRow == varData.rowValues(2), "Wrong third row");
    QVERIFY2(expectedFourthRow == varData.rowValues(3), "Wrong fourth row");
    QVERIFY2(expectedFifthRow == varData.rowValues(4), "Wrong fifth row");
}

void TestReader::testReadFileWithSemicolons()
{
    const QString path = getPathToFileTestSemicolon();
    QList<QStringList> data = QtCSV::Reader::readToList(path, ";");

    QVERIFY2(false == data.isEmpty(), "Failed to read file content");
    QVERIFY2(2 == data.size(), "Wrong number of rows");

    QStringList expectedFirstRow;
    expectedFirstRow << "1" << "2" << "3";

    QStringList expectedSecondRow;
    expectedSecondRow << "j" << "io" << "pp";

    QVERIFY2(expectedFirstRow == data.at(0), "Wrong first row");
    QVERIFY2(expectedSecondRow == data.at(1), "Wrong second row");
}

void TestReader::testReadFileWithSemicolonsToStringData()
{
    const QString path = getPathToFileTestSemicolon();
    QtCSV::StringData strData;
    bool readResult = QtCSV::Reader::readToData(path, strData, ";");
    QVERIFY2(true == readResult, "Failed to read file content");

    QVERIFY2(false == strData.isEmpty(), "Failed to read file content");
    QVERIFY2(2 == strData.rowCount(), "Wrong number of rows");

    QStringList expectedFirstRow;
    expectedFirstRow << "1" << "2" << "3";

    QStringList expectedSecondRow;
    expectedSecondRow << "j" << "io" << "pp";

    QVERIFY2(expectedFirstRow == strData.rowValues(0), "Wrong first row");
    QVERIFY2(expectedSecondRow == strData.rowValues(1), "Wrong second row");
}

void TestReader::testReadFileWithSemicolonsToVariantData()
{
    const QString path = getPathToFileTestSemicolon();
    QtCSV::VariantData varData;
    bool readResult = QtCSV::Reader::readToData(path, varData, ";");
    QVERIFY2(true == readResult, "Failed to read file content");

    QVERIFY2(false == varData.isEmpty(), "Failed to read file content");
    QVERIFY2(2 == varData.rowCount(), "Wrong number of rows");

    QStringList expectedFirstRow;
    expectedFirstRow << "1" << "2" << "3";

    QStringList expectedSecondRow;
    expectedSecondRow << "j" << "io" << "pp";

    QVERIFY2(expectedFirstRow == varData.rowValues(0), "Wrong first row");
    QVERIFY2(expectedSecondRow == varData.rowValues(1), "Wrong second row");
}

void TestReader::testReadFileWithCommasAndDataWithSeparators()
{
    const QString path = getPathToFileTestDataWithSeparators();
    QList<QStringList> data = QtCSV::Reader::readToList(path, ",", "\"");

    QVERIFY2(false == data.isEmpty(), "Failed to read file content");
    QVERIFY2(6 == data.size(), "Wrong number of rows");

    QList<QStringList> expected;
    expected << (QStringList() << "one" << "two" << "three, four" << "five");
    expected << (QStringList() << "this, is, one, element");
    expected << (QStringList() << "test" << "this \"example" << "to find\"" <<
                 "bugs");
    expected << (QStringList() << "six" << "seven" << "\"eight");
    expected << (QStringList() << "nine" << "\"ten,eleven");
    expected << (QStringList() << "twelve" << "thirteen" << "14" << "15.16");

    for (int i = 0; i < data.size(); ++i)
    {
        qDebug() << data.at(i);
        QVERIFY2(expected.at(i) == data.at(i), "Wrong row data");
    }
}

QString TestReader::getPathToFolderWithTestFiles() const
{
    return QDir::currentPath() + "/data/";
}

QString TestReader::getPathToFileTestComma() const
{
    return getPathToFolderWithTestFiles() + "test-comma.csv";
}

QString TestReader::getPathToFileTestSemicolon() const
{
    return getPathToFolderWithTestFiles() + "test-semicolon.csv";
}

QString TestReader::getPathToFileTestDataWithSeparators() const
{
    return getPathToFolderWithTestFiles() + "test-data-with-separators.csv";
}
