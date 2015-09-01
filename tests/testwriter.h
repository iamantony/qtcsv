#ifndef TESTWRITER_H
#define TESTWRITER_H

#include <QObject>
#include <QtTest>

#include "stringdata.h"

class TestWriter : public QObject
{
    Q_OBJECT

public:
    TestWriter();

private Q_SLOTS:
    void cleanup();
    void testWriteInvalidArgs();
    void testWriteFromStringData();
    void testWriteFromVariantData();
    void testWriteAppendMode();
    void testWriteWithNotDefaultSeparator();
    void testWriteWithHeader();
    void testWriteWithFooter();
    void testWriteWithHeaderAndFooter();
    void testWriteDifferentDataAmount();

private:
    QString getFilePath() const;
    QtCSV::StringData getTestStringData(const int &symbolsInRow,
                                        const int &rowsNumber);
};

#endif // TESTWRITER_H
