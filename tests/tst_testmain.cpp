#include <QtTest>

#include "teststringdata.h"
#include "testvariantdata.h"
#include "testreader.h"
#include "testwriter.h"

int main(int argc, char** argv)
{
    int status = 0;
    auto ASSERT_TEST = [&status, argc, argv](QObject* obj) {
      status |= QTest::qExec(obj, argc, argv);
      delete obj;
    };

    ASSERT_TEST(new TestStringData());
    ASSERT_TEST(new TestVariantData());
    ASSERT_TEST(new TestReader());
    ASSERT_TEST(new TestWriter());

    return status;
}
