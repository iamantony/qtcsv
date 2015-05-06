#include "teststringdata.h"
#include "stringdata.h"

TestStringData::TestStringData()
{
}

void TestStringData::testCreation()
{
    QtCSV::StringData strData;

    QVERIFY2(strData.isEmpty(), "Empty StringData is not empty");
    QVERIFY2(strData.getNumberOfRows() == 0,
             "Empty StringData have too many rows");
}

void TestStringData::testAddEmptyRow()
{
    QtCSV::StringData strData;
    strData.addEmptyRow();

    QVERIFY2(false == strData.isEmpty(), "StringData is empty with empty line");
    QVERIFY2(1 == strData.getNumberOfRows(), "Wrong number of rows");
    QVERIFY2(QStringList() == strData.getRowValues(0),
             "Wrong data for empty row");
}

void TestStringData::testAddOneRow()
{
    QStringList rowValues;
    rowValues << "one" << "two" << "three";

    QtCSV::StringData strData;
    strData.addRow(rowValues);

    QVERIFY2(false == strData.isEmpty(), "StringData is empty");
    QVERIFY2(1 == strData.getNumberOfRows(), "Wrong number of rows");
    QVERIFY2(rowValues == strData.getRowValues(0), "Wrong data for empty row");
}

void TestStringData::testAddRows()
{
    QStringList valuesFirst;
    valuesFirst << "1" << "2" << "3";

    QStringList valuesSecond;

    QStringList valuesThird;
    valuesFirst << "hhh" << "ttyyeeqp[" << "n...589129";

    QtCSV::StringData strData;
    strData.addRow(valuesFirst);
    strData.addRow(valuesSecond);
    strData.addRow(valuesThird);

    QVERIFY2(false == strData.isEmpty(), "StringData is empty");
    QVERIFY2(3 == strData.getNumberOfRows(), "Wrong number of rows");
    QVERIFY2(valuesFirst == strData.getRowValues(0),
             "Wrong data for first row");
    QVERIFY2(valuesSecond == strData.getRowValues(1),
             "Wrong data for second row");
    QVERIFY2(valuesThird == strData.getRowValues(2),
             "Wrong data for third row");
}

void TestStringData::testClearEmptyData()
{
    QtCSV::StringData strData;

    QVERIFY2(true == strData.isEmpty(), "StringData is not empty");

    strData.clear();

    QVERIFY2(true == strData.isEmpty(), "StringData is not empty");
}

void TestStringData::testClearNotEmptyData()
{
    QStringList rowValues;
    rowValues << "one" << "two" << "three";

    QtCSV::StringData strData;
    strData.addRow(rowValues);

    QVERIFY2(false == strData.isEmpty(), "StringData is empty");

    strData.clear();

    QVERIFY2(true == strData.isEmpty(), "StringData is not empty");
}
