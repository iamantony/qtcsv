#ifndef TESTVARIANTDATA_H
#define TESTVARIANTDATA_H

#include <QObject>
#include <QtTest>

class TestVariantData : public QObject
{
    Q_OBJECT

public:
    TestVariantData();

private Q_SLOTS:
    void testCreation();
    void testAddEmptyRow();
    void testAddOneRow();
    void testAddRows();
    void testClearEmptyData();
    void testClearNotEmptyData();
};

#endif // TESTVARIANTDATA_H
