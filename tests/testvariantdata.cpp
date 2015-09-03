#include "testvariantdata.h"
#include "variantdata.h"

TestVariantData::TestVariantData()
{
}

void TestVariantData::testCreation()
{
    QtCSV::VariantData varData;

    QVERIFY2(varData.isEmpty(), "Empty VariantData is not empty");
    QVERIFY2(varData.getNumberOfRows() == 0,
             "Empty VariantData have too many rows");
}

void TestVariantData::testAddEmptyRow()
{
    QtCSV::VariantData varData;
    varData.addEmptyRow();

    QVERIFY2(false == varData.isEmpty(), "VariantData is empty with empty line");
    QVERIFY2(1 == varData.getNumberOfRows(), "Wrong number of rows");
    QVERIFY2(QStringList() == varData.getRowValues(0),
             "Wrong data for empty row");
}

void TestVariantData::testAddOneRow()
{
    int expectedValue = 42;
    QVariant varValue(expectedValue);

    QtCSV::VariantData varData;
    varData.addRow(varValue);

    QVERIFY2(false == varData.isEmpty(), "VariantData is empty");
    QVERIFY2(1 == varData.getNumberOfRows(), "Wrong number of rows");

    QStringList values = varData.getRowValues(0);
    QVERIFY2(1 == values.size(), "Wrong number of values");

    int resultValue = values.at(0).toInt();
    QVERIFY2(resultValue == expectedValue, "Wrong data");
}

void TestVariantData::testAddRows()
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

    QVERIFY2(false == varData.isEmpty(), "VariantData is empty");
    QVERIFY2(3 == varData.getNumberOfRows(), "Wrong number of rows");

    QStringList values = varData.getRowValues(0);
    QVERIFY2(1 == values.size(), "Wrong number of values for first row");

    double resultValue = values.at(0).toDouble();
    QVERIFY2(resultValue == expectedValue, "Wrong double value");

    QStringList secondRowValues = varData.getRowValues(1);
    QVERIFY2(secondRow.size() == secondRowValues.size(),
             "Wrong number of elements in second row");

    QVERIFY2(secondRow.at(0).toString() == secondRowValues.at(0),
             "Wrong first element in second row");

    QVERIFY2(secondRow.at(1).toInt() == secondRowValues.at(1).toInt(),
             "Wrong second element in second row");

    QVERIFY2(secondRow.at(2).toDouble() == secondRowValues.at(2).toDouble(),
             "Wrong third element in second row");

    QVERIFY2(thirdRow == varData.getRowValues(2), "Wrong third row values");
}

void TestVariantData::testClearEmptyData()
{
    QtCSV::VariantData varData;

    QVERIFY2(true == varData.isEmpty(), "VariantData is not empty");
    QVERIFY2(0 == varData.getNumberOfRows(), "Wrong number of rows");

    varData.clear();

    QVERIFY2(true == varData.isEmpty(), "VariantData is not empty");
    QVERIFY2(0 == varData.getNumberOfRows(), "Wrong number of rows");
}

void TestVariantData::testClearNotEmptyData()
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

    QVERIFY2(false == varData.isEmpty(), "VariantData is empty");
    QVERIFY2(3 == varData.getNumberOfRows(), "Wrong number of rows");

    varData.clear();

    QVERIFY2(true == varData.isEmpty(), "VariantData is not empty");
    QVERIFY2(0 == varData.getNumberOfRows(), "Wrong number of rows");
}

void TestVariantData::testCompareForEquality()
{
    QStringList firstRow, secondRow;
    firstRow << "one" << "two" << "three";
    secondRow << "four" << "five";

    QtCSV::VariantData firstData;
    firstData.addRow(firstRow);
    firstData.addRow(secondRow);

    QtCSV::VariantData secondData;
    secondData.addRow(firstRow);
    secondData.addRow(secondRow);

    QVERIFY2(firstData == secondData, "Objects are not the same");
    QVERIFY2(false == (firstData != secondData), "Objects are not the same");

    secondData.addRow(firstRow);

    QVERIFY2(false == (firstData == secondData), "Objects are the same");
    QVERIFY2(firstData != secondData, "Objects are the same");
}

void TestVariantData::testCopyConstruction()
{
    QStringList firstRow, secondRow;
    firstRow << "one" << "two" << "three";
    secondRow << "four" << "five";

    QtCSV::VariantData firstData;
    firstData.addRow(firstRow);
    firstData.addRow(secondRow);

    QtCSV::VariantData secondData(firstData);

    QVERIFY2(firstData.getNumberOfRows() == secondData.getNumberOfRows(),
             "Wrong number of rows");
    QVERIFY2(firstRow == secondData.getRowValues(0),
             "Wrong data for first row");
    QVERIFY2(secondRow == secondData.getRowValues(1),
             "Wrong data for second row");
}

void TestVariantData::testCopyAssignment()
{
    QStringList firstRow, secondRow;
    firstRow << "one" << "two" << "three";
    secondRow << "four" << "five";

    QtCSV::VariantData firstData;
    firstData.addRow(firstRow);
    firstData.addRow(secondRow);

    QtCSV::VariantData secondData;
    secondData = firstData;

    QVERIFY2(firstData.getNumberOfRows() == secondData.getNumberOfRows(),
             "Wrong number of rows");
    QVERIFY2(firstRow == secondData.getRowValues(0),
             "Wrong data for first row");
    QVERIFY2(secondRow == secondData.getRowValues(1),
             "Wrong data for second row");
}

void TestVariantData::testOperatorInput()
{
    QtCSV::VariantData data;
    data << QString("1") << QVariant(double(3.14));

    QStringList thirdRow;
    thirdRow << "one" << "two" << "three";

    data << thirdRow;

    QVERIFY2(3 == data.getNumberOfRows(), "Wrong number of rows");

    QStringList expectedFirstRow, expectedSecondRow;
    expectedFirstRow << "1";
    expectedSecondRow << QVariant(double(3.14)).toString();

    QVERIFY2(expectedFirstRow == data.getRowValues(0),
             "Wrong data for first row");
    QVERIFY2(expectedSecondRow == data.getRowValues(1),
             "Wrong data for second row");
    QVERIFY2(thirdRow == data.getRowValues(2),
             "Wrong data for third row");
}
