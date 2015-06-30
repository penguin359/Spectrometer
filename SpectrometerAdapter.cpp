#include <arduino.h>

#include "SpectrometerAdapter.h"

AdafruitSpectrometerAdapter::
	AdafruitSpectrometerAdapter(Adafruit_StepperMotor *newMotor,
			    uint8_t newLowLimitPin,
			    uint8_t newHighLimitPin) :
    motor(newMotor), lowLimitPin(newLowLimitPin), highLimitPin(newHighLimitPin)
{
}

void AdafruitSpectrometerAdapter::begin()
{
	pinMode(lowLimitPin, INPUT);
	pinMode(highLimitPin, INPUT);
	motor->setSpeed(maxSpeed);
}

void AdafruitSpectrometerAdapter::step(int dir)
{
	motor->step(1, dir, SINGLE);
}

uint8_t AdafruitSpectrometerAdapter::lowLimitHit()
{
	return digitalRead(lowLimitPin);
}

uint8_t AdafruitSpectrometerAdapter::highLimitHit()
{
	return digitalRead(highLimitPin);
}


CounterSpectrometerAdapter::CounterSpectrometerAdapter(int newLowLimit, int newHighLimit) :
	position(newLowLimit), lowLimit(newLowLimit), highLimit(newHighLimit)
{
}

void CounterSpectrometerAdapter::begin()
{
}

void CounterSpectrometerAdapter::step(int dir)
{
	if(dir == FORWARD)
		position++;
	else
		position--;
}

int CounterSpectrometerAdapter::getPosition()
{
	return position;
}

void CounterSpectrometerAdapter::setPosition(int newPosition)
{
	position = newPosition;
}

uint8_t CounterSpectrometerAdapter::lowLimitHit()
{
	return position <= lowLimit;
}

uint8_t CounterSpectrometerAdapter::highLimitHit()
{
	return position >= highLimit;
}

int CounterSpectrometerAdapter::outOfBounds()
{
	return position < lowLimit || position > highLimit;
}
