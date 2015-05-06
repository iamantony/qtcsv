#ifndef TESTWRITER_H
#define TESTWRITER_H

#include <QObject>
#include <QtTest>

class TestWriter : public QObject
{
    Q_OBJECT

public:
    TestWriter();

private Q_SLOTS:
    void cleanup();
    void testWriteFromStringData();
    void testWriteFromVariantData();
    void testWriteAppendMode();
    void testWriteWithNotDefaultSeparator();
    void testWriteWithHeader();
    void testWriteWithFooter();
    void testWriteWithHeaderAndFooter();

private:
    QString getFilePath() const;
};

#endif // TESTWRITER_H
