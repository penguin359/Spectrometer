#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "CppUTest/CommandLineTestRunner.h"

#include "Arduino.h"
#include "Adafruit_MotorShield.h"
#include "SpectrometerAdapter.h"
#include "Spectrometer.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *stepper = AFMS.getStepper(200, 1);

/* XXX TODO Test Spectrometer begin!!!
 * check limits
 * check limit recovery
 * check limit direction
 * check wavelength stopped at right value
 * echo serial
 * move ratio from 1 to 52
 * merge moveTo() code
 */

TEST_GROUP(StepperMotor)
{
	void setup()
	{
		AFMS.begin();
	}

	void teardown()
	{
		mock().clear();
	}
};

TEST(StepperMotor, Step)
{
	mock().expectOneCall("step").onObject(stepper).withParameter("steps", 0).withParameter("dir", 0).withParameter("style", 0);
	stepper->step(0, 0, 0);
	mock().checkExpectations();
}

TEST(StepperMotor, setSpeed)
{
	mock().expectOneCall("setSpeed").onObject(stepper).withParameter("rpm", 0);
	stepper->setSpeed(0);
	mock().checkExpectations();
}

TEST(StepperMotor, onestep)
{
	uint8_t retval;

	mock().expectOneCall("onestep").onObject(stepper).withParameter("dir", 0).withParameter("style", 0).andReturnValue(2);
	retval = stepper->onestep(0, 0);
	LONGS_EQUAL(2, retval);
	mock().checkExpectations();
}


TEST_GROUP(Spectrometer)
{
	void setup()
	{
		AFMS.begin();
	}

	void teardown()
	{
		mock().clear();
	}
};

TEST(Spectrometer, MoveUp)
{
	Spectrometer spectrometer(stepper);

	mock().expectOneCall("step").onObject(stepper).withParameter("steps", 1).withParameter("dir", FORWARD).withParameter("style", SINGLE);
	spectrometer.up();
	mock().checkExpectations();
}

IGNORE_TEST(Spectrometer, MoveUp)
{
	Spectrometer spectrometer(stepper);

	mock().expectOneCall("step").onObject(stepper).withParameter("steps", 1).withParameter("dir", FORWARD).withParameter("style", SINGLE);
	spectrometer.setDisplayedWavelength(1000);
	spectrometer.up();
	mock().checkExpectations();
}

TEST(Spectrometer, SecondTest)
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
	mock().actualCall("productionCode");
}

TEST(MockDocumentation, SimpleScenario)
{
	mock().expectOneCall("productionCode");
	productionCode();
	mock().checkExpectations();
}

/* XXX Move inside TEST_GROUP */
enum { LOW_LIMIT_SWITCH_PIN = 2, HIGH_LIMIT_SWITCH_PIN = 5 };
SpectrometerAdapter *adapter = new AdafruitSpectrometerAdapter(stepper, LOW_LIMIT_SWITCH_PIN, HIGH_LIMIT_SWITCH_PIN);

TEST_GROUP(AdafruitSpectrometerAdapter)
{
	void setup()
	{
		pinInit();
		AFMS.begin();
	}

	void teardown()
	{
		mock().clear();
	}
};

TEST(AdafruitSpectrometerAdapter, Initialized)
{
	AdafruitSpectrometerAdapter adapter(stepper, 0, 0);

	mock().expectOneCall("setSpeed").onObject(stepper).withParameter("rpm", AdafruitSpectrometerAdapter::maxSpeed);
	adapter.begin();
	mock().checkExpectations();
}

TEST(AdafruitSpectrometerAdapter, OneStep)
{
	mock().expectOneCall("step").onObject(stepper).withParameter("steps", 1).withParameter("dir", FORWARD).withParameter("style", SINGLE);
	adapter->step(FORWARD);
	mock().checkExpectations();
}

TEST(AdafruitSpectrometerAdapter, ReadLowLimitSwitch)
{
	LONGS_EQUAL(LOW, adapter->lowLimitHit());
	digitalRead_Set(LOW_LIMIT_SWITCH_PIN, HIGH);
	LONGS_EQUAL(HIGH, adapter->lowLimitHit());
	digitalRead_Set(LOW_LIMIT_SWITCH_PIN, LOW);
	LONGS_EQUAL(LOW, adapter->lowLimitHit());
}

TEST(AdafruitSpectrometerAdapter, ReadHighLimitSwitch)
{
	LONGS_EQUAL(LOW, adapter->highLimitHit());
	digitalRead_Set(HIGH_LIMIT_SWITCH_PIN, HIGH);
	LONGS_EQUAL(HIGH, adapter->highLimitHit());
	digitalRead_Set(HIGH_LIMIT_SWITCH_PIN, LOW);
	LONGS_EQUAL(LOW, adapter->highLimitHit());
}

TEST(AdafruitSpectrometerAdapter, InitializesLimitSwitchesAsInput)
{
	pinMode(LOW_LIMIT_SWITCH_PIN, OUTPUT);
	pinMode(HIGH_LIMIT_SWITCH_PIN, OUTPUT);
	mock().expectOneCall("setSpeed").onObject(stepper).withParameter("rpm", AdafruitSpectrometerAdapter::maxSpeed);
	adapter->begin();
	LONGS_EQUAL(INPUT, pinMode_Get(LOW_LIMIT_SWITCH_PIN));
	LONGS_EQUAL(INPUT, pinMode_Get(HIGH_LIMIT_SWITCH_PIN));
}


TEST_GROUP(CounterSpectrometerAdapter)
{
	enum { LOW_LIMIT = 10, HIGH_LIMIT = 20 };

	CounterSpectrometerAdapter *adapter;

	void setup()
	{
		adapter = new CounterSpectrometerAdapter(LOW_LIMIT, HIGH_LIMIT);
		adapter->begin();
	}

	void teardown()
	{
		delete adapter;
	}
};

TEST(CounterSpectrometerAdapter, Initialized)
{
	LONGS_EQUAL(LOW_LIMIT, adapter->getPosition());
}

TEST(CounterSpectrometerAdapter, CanSetPosition)
{
	adapter->setPosition(25);
	LONGS_EQUAL(25, adapter->getPosition());
	adapter->setPosition(-10);
	LONGS_EQUAL(-10, adapter->getPosition());
}

TEST(CounterSpectrometerAdapter, CanStepForward)
{
	adapter->setPosition(15);
	adapter->step(FORWARD);
	adapter->step(FORWARD);
	adapter->step(FORWARD);
	LONGS_EQUAL(18, adapter->getPosition());
}

TEST(CounterSpectrometerAdapter, CanStepBackwards)
{
	adapter->setPosition(15);
	adapter->step(BACKWARD);
	adapter->step(BACKWARD);
	adapter->step(BACKWARD);
	LONGS_EQUAL(12, adapter->getPosition());
}

TEST(CounterSpectrometerAdapter, HitsLowLimit)
{
	adapter->setPosition(LOW_LIMIT+1);
	LONGS_EQUAL(LOW, adapter->lowLimitHit());
	adapter->setPosition(LOW_LIMIT);
	LONGS_EQUAL(HIGH, adapter->lowLimitHit());
	adapter->setPosition(LOW_LIMIT-1);
	LONGS_EQUAL(HIGH, adapter->lowLimitHit());
}

TEST(CounterSpectrometerAdapter, HitsHighLimit)
{
	adapter->setPosition(HIGH_LIMIT-1);
	LONGS_EQUAL(LOW, adapter->highLimitHit());
	adapter->setPosition(HIGH_LIMIT);
	LONGS_EQUAL(HIGH, adapter->highLimitHit());
	adapter->setPosition(HIGH_LIMIT+1);
	LONGS_EQUAL(HIGH, adapter->highLimitHit());
}

TEST(CounterSpectrometerAdapter, CheckOutOfBounds)
{
	adapter->setPosition(HIGH_LIMIT-1);
	LONGS_EQUAL(0, adapter->outOfBounds());
	adapter->step(FORWARD);
	LONGS_EQUAL(0, adapter->outOfBounds());
	adapter->step(FORWARD);
	LONGS_EQUAL(1, adapter->outOfBounds());

	adapter->setPosition(LOW_LIMIT+1);
	LONGS_EQUAL(0, adapter->outOfBounds());
	adapter->step(BACKWARD);
	LONGS_EQUAL(0, adapter->outOfBounds());
	adapter->step(BACKWARD);
	LONGS_EQUAL(1, adapter->outOfBounds());
}

int main(int ac, char** av)
{
	return CommandLineTestRunner::RunAllTests(ac, av);
}
