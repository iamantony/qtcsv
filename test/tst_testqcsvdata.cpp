#include <QString>
#include <QtTest>

class TestQCSVData : public QObject
{
	Q_OBJECT

public:
	TestQCSVData();

private Q_SLOTS:
	void testCase1();
};

TestQCSVData::TestQCSVData()
{
}

void TestQCSVData::testCase1()
{
	QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestQCSVData)

#include "tst_testqcsvdata.moc"
