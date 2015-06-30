#include <arduino.h>

#include "SpectrometerAdapter.h"

SpectrometerAdapter::
	SpectrometerAdapter(Adafruit_StepperMotor *newMotor,
			    uint8_t newLowLimitPin,
			    uint8_t newHighLimitPin) :
    motor(newMotor), lowLimitPin(newLowLimitPin), highLimitPin(newHighLimitPin)
{
}

void SpectrometerAdapter::begin()
{
	pinMode(lowLimitPin, INPUT);
	pinMode(highLimitPin, INPUT);
	motor->setSpeed(maxSpeed);
}

void SpectrometerAdapter::step(int dir)
{
	motor->step(1, dir, SINGLE);
}

uint8_t SpectrometerAdapter::lowLimitHit()
{
	return digitalRead(lowLimitPin);
}

uint8_t SpectrometerAdapter::highLimitHit()
{
	return digitalRead(highLimitPin);
}
