#include <QtTest>

#include "teststringdata.h"
#include "testvariantdata.h"

int main(int argc, char** argv)
{
    int status = 0;
    auto ASSERT_TEST = [&status, argc, argv](QObject* obj) {
      status |= QTest::qExec(obj, argc, argv);
      delete obj;
    };

    ASSERT_TEST(new TestStringData());
    ASSERT_TEST(new TestVariantData());

    return status;
}
