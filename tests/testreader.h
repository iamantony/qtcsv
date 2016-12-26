#ifndef TESTREADER_H
#define TESTREADER_H

#include <QObject>
#include <QtTest>

class TestReader : public QObject
{
    Q_OBJECT

public:
    TestReader();

private Q_SLOTS:
    void testReadToListInvalidArgs();
    void testReadToDataInvalidArgs();
    void testReadFileWithCommas();
    void testReadFileWithDotsInName();
    void testReadFileWithCommasToStringData();
    void testReadFileWithCommasToVariantData();
    void testReadFileWithSemicolons();
    void testReadFileWithSemicolonsToStringData();
    void testReadFileWithSemicolonsToVariantData();
    void testReadFileWithTextDelimDQoutes();
    void testReadFileWithTextDelimQoutes();
    void testReadFileWithTextDelimDQToStringData();
    void testReadLongWithDQuotes();
    void testReadFieldWithCRLF();
    void testReadFieldWithCRLFLong();
    void testReadFieldEndTripleQuotes();
    void testReadFieldCorrectness();

private:
    QString getPathToFolderWithTestFiles() const;
    QString getPathToFileTestComma() const;
    QString getPathToFileTestDotsInName() const;
    QString getPathToFileTestSemicolon() const;
    QString getPathToFileTestDataTextDelimDQuotes() const;
    QString getPathToFileTestDataTextDelimQuotes() const;
    QString getPathToFileTestFieldWithDQuotes() const;
    QString getPathToFileTestFieldWithCRLF() const;
    QString getPathToFileTestFieldWithCRLFLong() const;
    QString getPathToFileTestFieldEndTripleQuotes() const;
    QString getPathToFileTestDataCorrectness() const;
};

#endif // TESTREADER_H
