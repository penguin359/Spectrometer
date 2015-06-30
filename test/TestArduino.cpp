#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include <CppUTest/CommandLineTestRunner.h>

#include <Arduino.h>


/* TODO Check pin out of range values
 * digitalRead() returns LOW on invalid pin
 */

TEST_GROUP(ArduinoGpio)
{
	void setup()
	{
		pinInit();
	}
};

TEST(ArduinoGpio, AllPinsInitiallyInput)
{
	int i;

	for(i = 0; i < NUM_DIGITAL_PINS; i++) {
		LONGS_EQUAL(INPUT, pinMode_Get(i));
	}
}

TEST(ArduinoGpio, AllPinsInitiallyReadLow)
{
	int i;

	for(i = 0; i < NUM_DIGITAL_PINS; i++) {
		LONGS_EQUAL(LOW, digitalRead(i));
	}
}

TEST(ArduinoGpio, CanSetInputsToReadHigh)
{
	digitalRead_Set(0, HIGH);
	digitalRead_Set(1, LOW);
	digitalRead_Set(3, HIGH);
	LONGS_EQUAL(HIGH, digitalRead(0));
	LONGS_EQUAL(LOW, digitalRead(1));
	LONGS_EQUAL(LOW, digitalRead(2));
	LONGS_EQUAL(HIGH, digitalRead(3));
}

TEST(ArduinoGpio, MakeOnlyOnePinOutput)
{
	pinMode(0, OUTPUT);
	LONGS_EQUAL(OUTPUT, pinMode_Get(0));
	LONGS_EQUAL(INPUT, pinMode_Get(1));
}

TEST(ArduinoGpio, CanReadBackOutputPin)
{
	pinMode(0, OUTPUT);
	LONGS_EQUAL(LOW, digitalRead(0));
	digitalWrite(0, HIGH);
	LONGS_EQUAL(HIGH, digitalRead(0));
	digitalWrite(0, LOW);
	LONGS_EQUAL(LOW, digitalRead(0));
}

TEST(ArduinoGpio, PinOutputValueDoesChangeInputValue)
{
	pinMode(0, OUTPUT);
	LONGS_EQUAL(LOW, digitalRead(0));
	digitalWrite(0, HIGH);
	LONGS_EQUAL(HIGH, digitalRead(0));
	pinMode(0, INPUT);
	LONGS_EQUAL(LOW, digitalRead(0));
}

//TEST(ArduinoGpio, 
int main(int ac, char** av)
{
	return CommandLineTestRunner::RunAllTests(ac, av);
}
