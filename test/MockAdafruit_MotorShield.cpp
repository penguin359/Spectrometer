#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "Adafruit_MotorShield.h"


Adafruit_PWMServoDriver::Adafruit_PWMServoDriver(uint8_t addr)
{
}


Adafruit_DCMotor::Adafruit_DCMotor(void)
{
}


Adafruit_StepperMotor::Adafruit_StepperMotor(void)
{
}

void Adafruit_StepperMotor::step(uint16_t steps, uint8_t dir,  uint8_t style)
{
	mock().actualCall("step").onObject(this).withParameter("steps", steps).withParameter("dir", dir).withParameter("style", style);
}

void Adafruit_StepperMotor::setSpeed(uint16_t rpm)
{
	mock().actualCall("setSpeed").onObject(this).withParameter("rpm", rpm);
}

uint8_t Adafruit_StepperMotor::onestep(uint8_t dir, uint8_t style)
{
	mock().actualCall("onestep").onObject(this).withParameter("dir", dir).withParameter("style", style);
	return mock().intReturnValue();
}

void Adafruit_StepperMotor::release(void)
{
	//mock().actualCall("release").onObject(this);
}


Adafruit_MotorShield::Adafruit_MotorShield(uint8_t addr)
{
}

void Adafruit_MotorShield::begin(uint16_t freq)
{
}

Adafruit_StepperMotor *Adafruit_MotorShield::getStepper(uint16_t steps, uint8_t n)
{
	n--;
	if(n >= sizeof(steppers)/sizeof(steppers[0]))
		return NULL;
	return &steppers[n];
}
