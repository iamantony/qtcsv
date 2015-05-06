#ifndef TESTSTRINGDATA_H
#define TESTSTRINGDATA_H

#include <QString>
#include <QtTest>

class TestStringData : public QObject
{
    Q_OBJECT

public:
    TestStringData();

private Q_SLOTS:
    void testCreation();
    void testAddEmptyRow();
    void testAddOneRow();
    void testAddRows();
    void testClearEmptyData();
    void testClearNotEmptyData();
};

#endif // TESTSTRINGDATA_H
