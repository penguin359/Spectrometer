#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "CppUTest/CommandLineTestRunner.h"

TEST_GROUP(FirstTestGroup)
{
};

TEST(FirstTestGroup, FirstTest)
{
	//FAIL("Fail me!");
}

TEST(FirstTestGroup, SecondTest)
{
	//STRCMP_EQUAL("hello", "world");
	STRCMP_EQUAL("hello", "hello");
	//LONGS_EQUAL(1, 2);
	LONGS_EQUAL(1, 1);
	//CHECK(false);
	CHECK(true);
}

TEST_GROUP(MockDocumentation)
{
	void teardown()
	{
		mock().clear();
	}
};

void productionCode()
{
	mock().actualCall("pxoductionCode");
}

TEST(MockDocumentation, SimpleScenario)
{
	mock().expectOneCall("productionCode");
	productionCode();
	mock().checkExpectations();
}

int main(int ac, char** av)
{
	return CommandLineTestRunner::RunAllTests(ac, av);
}
