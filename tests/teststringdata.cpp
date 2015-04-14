#include "teststringdata.h"
#include "stringdata.h"

TestStringData::TestStringData()
{
}

void TestStringData::testCreation()
{
    QtCSV::StringData strData;
    QVERIFY2(strData.isEmpty(), "Empty data is not empty");
    QVERIFY2(strData.getNumberOfRows() == 0, "Empty data have too many rows");
}

void TestStringData::testAddEmptyRow()
{
    QtCSV::StringData strData;
    strData.addEmptyRow();
    QVERIFY2(false == strData.isEmpty(), "Data empty with empty line");
    QVERIFY2(1 == strData.getNumberOfRows(), "Wrong number of rows");
    QVERIFY2(QStringList() == strData.getRowValues(0),
             "Wrong data for empty row");
}
