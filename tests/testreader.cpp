#include "testreader.h"
#include "qtcsv/reader.h"
#include "qtcsv/stringdata.h"
#include "qtcsv/variantdata.h"
#include <QDir>
#include <QFile>
#include <QElapsedTimer>

TestReader::TestReader() {}

void TestReader::testReadToListInvalidArgs()
{
    QVERIFY2(QtCSV::Reader::readToList(QString(), QString()).empty(),
             "Invalid arguments was accepted");

    QVERIFY2(QtCSV::Reader::readToList(
                 getPathToFileTestComma(), QString()).empty(),
             "Invalid arguments was accepted");

    QVERIFY2(QtCSV::Reader::readToList(QString(), ",").empty(),
             "Invalid arguments was accepted");

    QVERIFY2(QtCSV::Reader::readToList("./some/path.csv", ",").empty(),
             "Invalid arguments was accepted");

    QVERIFY2(QtCSV::Reader::readToList(
                 getPathToFileTestComma() + ".md5", ",").empty(),
             "Invalid arguments was accepted");
}

void TestReader::testReadToDataInvalidArgs()
{
    QtCSV::StringData data;

    QVERIFY2(false == QtCSV::Reader::readToData(QString(), data, QString()),
             "Invalid arguments was accepted");

    QVERIFY2(false == QtCSV::Reader::readToData(
                 getPathToFileTestComma(), data, QString()),
             "Invalid arguments was accepted");

    QVERIFY2(false == QtCSV::Reader::readToData(QString(), data, ","),
             "Invalid arguments was accepted");

    QVERIFY2(false == QtCSV::Reader::readToData("./some/path.csv", data, ","),
             "Invalid arguments was accepted");

    QVERIFY2(false == QtCSV::Reader::readToData(
                 getPathToFileTestComma() + ".md5", data, ","),
             "Invalid arguments was accepted");
}

void TestReader::testReadFileWithCommas()
{
    const QString path = getPathToFileTestComma();
    QList<QList<QString>> data = QtCSV::Reader::readToList(path);

    QVERIFY2(false == data.isEmpty(), "Failed to read file content");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << "one" << "two" << "three");
    expected << (QList<QString>() << "one_element");
    expected << (QList<QString>() << "1" << "2" << "3");
    expected << (QList<QString>());
    expected << (QList<QString>() << "3.14");

    QVERIFY2(expected.size() == data.size(), "Wrong number of rows");
    for (int i = 0; i < data.size(); ++i)
    {
        QVERIFY2(expected.at(i) == data.at(i), "Wrong row data");
    }
}

void TestReader::testReadFileWithDotsInName()
{
    const QString path = getPathToFileTestDotsInName();
    QList<QList<QString>> data = QtCSV::Reader::readToList(path);

    QVERIFY2(false == data.isEmpty(), "Failed to read file content");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << "one" << "two" << "three");
    expected << (QList<QString>() << "one_element");

    QVERIFY2(expected.size() == data.size(), "Wrong number of rows");
    for (int i = 0; i < data.size(); ++i)
    {
        QVERIFY2(expected.at(i) == data.at(i), "Wrong row data");
    }
}

void TestReader::testReadFileWithCommasToStringData()
{
    const QString path = getPathToFileTestComma();
    QtCSV::StringData strData;
    bool readResult = QtCSV::Reader::readToData(path, strData);
    QVERIFY2(true == readResult, "Failed to read file content");
    QVERIFY2(false == strData.isEmpty(), "StringData is empty");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << "one" << "two" << "three");
    expected << (QList<QString>() << "one_element");
    expected << (QList<QString>() << "1" << "2" << "3");
    expected << (QList<QString>());
    expected << (QList<QString>() << "3.14");

    QVERIFY2(expected.size() == strData.rowCount(), "Wrong number of rows");
    for (int i = 0; i < strData.rowCount(); ++i)
    {
        QVERIFY2(expected.at(i) == strData.rowValues(i), "Wrong row data");
    }
}

void TestReader::testReadFileWithCommasToVariantData()
{
    const QString path = getPathToFileTestComma();
    QtCSV::VariantData varData;
    bool readResult = QtCSV::Reader::readToData(path, varData);
    QVERIFY2(true == readResult, "Failed to read file content");
    QVERIFY2(false == varData.isEmpty(), "StringData is empty");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << "one" << "two" << "three");
    expected << (QList<QString>() << "one_element");
    expected << (QList<QString>() << "1" << "2" << "3");
    expected << (QList<QString>());
    expected << (QList<QString>() << "3.14");

    QVERIFY2(expected.size() == varData.rowCount(), "Wrong number of rows");
    for (int i = 0; i < varData.rowCount(); ++i)
    {
        QVERIFY2(expected.at(i) == varData.rowValues(i), "Wrong row data");
    }
}

void TestReader::testReadFileWithSemicolons()
{
    const QString path = getPathToFileTestSemicolon();
    QList<QList<QString>> data = QtCSV::Reader::readToList(path, ";");

    QVERIFY2(false == data.isEmpty(), "Failed to read file content");
    QVERIFY2(2 == data.size(), "Wrong number of rows");

    QList<QString> expectedFirstRow;
    expectedFirstRow << "1" << "2" << "3";

    QList<QString> expectedSecondRow;
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

    QList<QString> expectedFirstRow;
    expectedFirstRow << "1" << "2" << "3";

    QList<QString> expectedSecondRow;
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

    QList<QString> expectedFirstRow;
    expectedFirstRow << "1" << "2" << "3";

    QList<QString> expectedSecondRow;
    expectedSecondRow << "j" << "io" << "pp";

    QVERIFY2(expectedFirstRow == varData.rowValues(0), "Wrong first row");
    QVERIFY2(expectedSecondRow == varData.rowValues(1), "Wrong second row");
}

void TestReader::testReadFileWithTextDelimDQoutes()
{
    const QString path = getPathToFileTestDataTextDelimDQuotes();
    QList<QList<QString>> data = QtCSV::Reader::readToList(path, ",", "\"");

    QVERIFY2(false == data.isEmpty(), "Failed to read file content");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << "one" << "two" << "three, four" << "five");
    expected << (QList<QString>() << "this, is, one, element");
    expected << (QList<QString>() << "six" << "seven" << "eight");

    QVERIFY2(expected.size() == data.size(), "Wrong number of rows");
    for (int i = 0; i < data.size(); ++i)
    {
        QVERIFY2(expected.at(i) == data.at(i), "Wrong row data");
    }
}

void TestReader::testReadFileWithTextDelimQoutes()
{
    const QString path = getPathToFileTestDataTextDelimQuotes();
    QList<QList<QString>> data = QtCSV::Reader::readToList(path, ",", "'");
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << "one" << "two" << "three, four" << "five");
    expected << (QList<QString>() << "this, is, one, element");
    expected << (QList<QString>() << "six" << "seven" << "eight");

    QVERIFY2(expected.size() == data.size(), "Wrong number of rows");
    for (int i = 0; i < data.size(); ++i)
    {
        QVERIFY2(expected.at(i) == data.at(i), "Wrong row data");
    }
}

void TestReader::testReadFileWithTextDelimDQToStringData()
{
    const QString path = getPathToFileTestDataTextDelimDQuotes();
    QtCSV::StringData strData;
    bool readResult = QtCSV::Reader::readToData(path, strData, ",", "\"");
    QVERIFY2(true == readResult, "Failed to read file content");
    QVERIFY2(false == strData.isEmpty(), "Failed to read file content");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << "one" << "two" << "three, four" << "five");
    expected << (QList<QString>() << "this, is, one, element");
    expected << (QList<QString>() << "six" << "seven" << "eight");

    QVERIFY2(expected.size() == strData.rowCount(), "Wrong number of rows");
    for (int i = 0; i < strData.rowCount(); ++i)
    {
        QVERIFY2(expected.at(i) == strData.rowValues(i), "Wrong row data");
    }
}

void TestReader::testReadLongWithDQuotes()
{
    const QString path = getPathToFileTestFieldWithDQuotes();
    QList<QList<QString>> data = QtCSV::Reader::readToList(path, ",", "\"");
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << "one" << "two" << "three");
    expected << (QList<QString>() << "four" << "very \"long\" field" << "five");
    expected << (QList<QString>() << "six" << "seven");

    QVERIFY2(expected.size() == data.size(), "Wrong number of rows");
    for (int i = 0; i < data.size(); ++i)
    {
        QVERIFY2(expected.at(i) == data.at(i), "Wrong row data");
    }
}

void TestReader::testReadFieldWithCR()
{
    const QString path = getPathToFileTestFieldWithCR();
    QList<QList<QString>> data = QtCSV::Reader::readToList(path, ";", "\"");
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << "Column1, Column2" << "Column3");
    expected << (QList<QString>() << " Hello with\r Hello again " << "Hello Col 3");

    QVERIFY2(expected.size() == data.size(), "Wrong number of rows");
    for (int i = 0; i < data.size(); ++i)
    {
        qWarning() << expected.at(i) << data.at(i);
        QVERIFY2(expected.at(i) == data.at(i), "Wrong row data");
    }
}

void TestReader::testReadFieldWithCRLF()
{
    const QString path = getPathToFileTestFieldWithCRLF();
    QList<QList<QString>> data = QtCSV::Reader::readToList(path, ",", "\"");
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << "one" << "two" << "three\nfour" << "five");
    expected << (QList<QString>() << "six" << "seven");

    QVERIFY2(expected.size() == data.size(), "Wrong number of rows");
    for (int i = 0; i < data.size(); ++i)
    {
        QVERIFY2(expected.at(i) == data.at(i), "Wrong row data");
    }
}

void TestReader::testReadFieldWithCRLFLong()
{
    const QString path = getPathToFileTestFieldWithCRLFLong();
    QList<QList<QString>> data = QtCSV::Reader::readToList(path, ",", "\"");
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << "one" << "two" <<
                 "three\nfour,\"five\n\"six\",seven\neight" << "nine");
    expected << (QList<QString>() << "ten" << "eleven");

    QVERIFY2(expected.size() == data.size(), "Wrong number of rows");
    for (int i = 0; i < data.size(); ++i)
    {
        QVERIFY2(expected.at(i) == data.at(i), "Wrong row data");
    }
}

void TestReader::testReadFieldEndTripleQuotes()
{
    const QString path = getPathToFileTestFieldEndTripleQuotes();
    QList<QList<QString>> data = QtCSV::Reader::readToList(path, ",", "\"");
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << "CCLK=\"yy/MM/dd,hh:mm:ssA+zz\"" << "test");
    expected << (QList<QString>() << "new" << "line \"it is\",\"def");

    QVERIFY2(expected.size() == data.size(), "Wrong number of rows");
    for (int i = 0; i < data.size(); ++i)
    {
        QVERIFY2(expected.at(i) == data.at(i), "Wrong row data");
    }
}

void TestReader::testReadFileDataCorrectness()
{
    const QString path = getPathToFileTestDataCorrectness();
    QList<QList<QString>> data = QtCSV::Reader::readToList(path, ",", "\"");
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << "Year" << "Make" << "Model" <<
                 "Description" << "Price");
    expected << (QList<QString>() <<  "1997" << "Ford" << "E350" <<
                 "ac, abs, moon" << "3000.00");
    expected << (QList<QString>() << "1999" << "Chevy" <<
                 "Venture \"Extended Edition\"" << "" << "4900.00");
    expected << (QList<QString>() << "1996" << "Jeep" << "Grand Cherokee" <<
                 "MUST SELL!\nair, moon roof, loaded" << "4799.00");
    expected << (QList<QString>() << "1999" << "Chevy" <<
                 "Venture \"Extended Edition, Very Large\"" << "" << "5000.00");
    expected << (QList<QString>() << "" << "" <<
                 "Venture \"Extended Edition\"" << "" << "4900.00");

    QVERIFY2(expected.size() == data.size(), "Wrong number of rows");
    for (int i = 0; i < data.size(); ++i)
    {
        QVERIFY2(expected.at(i) == data.at(i), "Wrong row data");
    }
}

void TestReader::testReadFileWorldCitiesPop()
{
    const QString path = getPathToFileWorldCitiesPop();
    if (false == QFile::exists(path))
    {
        qDebug() << "Skip testReadFileWorldCitiesPop() because file" << path <<
            "do not exist. If you want to run this test, download file "
            "from http://www.maxmind.com/download/worldcities/worldcitiespop.txt.gz";
        return;
    }

    QElapsedTimer timer;
    timer.start();
    QList<QList<QString>> data = QtCSV::Reader::readToList(path, ",", "\"");
    qDebug() << "Elapsed time:" << timer.elapsed() << "ms";

    QVERIFY2(false == data.isEmpty(), "Failed to read file content");
    QVERIFY2(3173959 == data.size(), "Wrong number of rows");
}

void TestReader::testReadFileWithEmptyFields()
{
    const QString path = getPathToFileWithEmptyFields();
    QList<QList<QString>> data = QtCSV::Reader::readToList(path, ",", "\"");
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << QString() << "0" << QString() << QString());

    QVERIFY2(expected.size() == data.size(), "Wrong number of rows");
    for (int i = 0; i < data.size(); ++i)
    {
        QVERIFY2(expected.at(i) == data.at(i), "Wrong row data");
    }
}

void TestReader::testReadFileWithEmptyFieldsComplexSeparator()
{
    const QString path = getPathToFileWithEmptyFieldsComplexSeparator();
    QList<QList<QString>> data = QtCSV::Reader::readToList(path, ";-;", "\"");
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << "0" << "1" << QString() << QString());
    expected << (QList<QString>() << QString() << "Question" << "158" <<
        QString() << QString());

    QVERIFY2(expected.size() == data.size(), "Wrong number of rows");
    for (int i = 0; i < data.size(); ++i)
    {
        QVERIFY2(expected.at(i) == data.at(i), "Wrong row data");
    }
}

void TestReader::testReadFileWithMultirowData()
{
    const QString path = getPathToFileMultirowData();
    QList<QList<QString>> data = QtCSV::Reader::readToList(path);
    QVERIFY2(false == data.isEmpty(), "Failed to read file content");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << "A" << "B" << "C" << "D");
    expected << (QList<QString>() << "a" << "b" << "c" << "d");
    expected << (QList<QString>() << "a" << "b field" << "c field\n" << "d field");
    expected << (QList<QString>() << "aa" << "bb" << "cc" << "dd");

    QVERIFY2(expected.size() == data.size(), "Wrong number of rows");
    for (int i = 0; i < data.size(); ++i)
    {
        QVERIFY2(expected.at(i) == data.at(i), "Wrong row data");
    }
}

void TestReader::testReadByProcessorWithBreak()
{
    class ProcessorWithBreak : public QtCSV::Reader::AbstractProcessor
    {
    public:
        size_t counter;
        QList<QList<QString>> data;

        ProcessorWithBreak()
        {
            counter = 0;
        }

        virtual bool processRowElements(const QList<QString>& elements)
        {
            if (counter < 2)
            {
                data << elements;
                ++counter;
            }

            return true;
        }
    };

    const QString path = getPathToFileMultirowData();
    ProcessorWithBreak processor;
    QVERIFY2(true == QtCSV::Reader::readToProcessor(path, processor),
             "Failed to read file content");

    QList<QList<QString>> expected;
    expected << (QList<QString>() << "A" << "B" << "C" << "D");
    expected << (QList<QString>() << "a" << "b" << "c" << "d");

    QVERIFY2(expected.size() == processor.data.size(), "Wrong number of rows");
    for (int i = 0; i < processor.data.size(); ++i)
    {
        QVERIFY2(expected.at(i) == processor.data.at(i), "Wrong row data");
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

QString TestReader::getPathToFileTestDotsInName() const
{
    return getPathToFolderWithTestFiles() + "test.file.dots.csv";
}

QString TestReader::getPathToFileTestSemicolon() const
{
    return getPathToFolderWithTestFiles() + "test-semicolon.csv";
}

QString TestReader::getPathToFileTestDataTextDelimDQuotes() const
{
    return getPathToFolderWithTestFiles() +
           "test-data-text-delim-double-quotes.csv";
}

QString TestReader::getPathToFileTestDataTextDelimQuotes() const
{
    return getPathToFolderWithTestFiles() + "test-data-text-delim-quotes.csv";
}

QString TestReader::getPathToFileTestFieldWithDQuotes() const
{
    return getPathToFolderWithTestFiles() + "test-field-with-dquotes.csv";
}

QString TestReader::getPathToFileTestFieldWithCR() const
{
    return getPathToFolderWithTestFiles() + "test-field-with-cr.csv";
}

QString TestReader::getPathToFileTestFieldWithCRLF() const
{
    return getPathToFolderWithTestFiles() + "test-field-with-crlf.csv";
}

QString TestReader::getPathToFileTestFieldWithCRLFLong() const
{
    return getPathToFolderWithTestFiles() + "test-field-with-crlf-long.csv";
}

QString TestReader::getPathToFileTestFieldEndTripleQuotes() const
{
    return getPathToFolderWithTestFiles() + "test-field-end-triple-quotes.csv";
}

QString TestReader::getPathToFileTestDataCorrectness() const
{
    return getPathToFolderWithTestFiles() + "test-data-correctness.csv";
}

QString TestReader::getPathToFileWorldCitiesPop() const
{
    return getPathToFolderWithTestFiles() + "worldcitiespop.txt";
}

QString TestReader::getPathToFileWithEmptyFields() const
{
    return getPathToFolderWithTestFiles() + "test-empty-fields.csv";
}

QString TestReader::getPathToFileWithEmptyFieldsComplexSeparator() const
{
    return getPathToFolderWithTestFiles() +
           "test-empty-fields-complex-separator.csv";
}

QString TestReader::getPathToFileMultirowData() const
{
    return getPathToFolderWithTestFiles() + "test-multirow-data.csv";
}
