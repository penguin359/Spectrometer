#include "SpectrometerAdapter.h"

SpectrometerAdapter::SpectrometerAdapter(Adafruit_StepperMotor *newMotor) :
    motor(newMotor)
{
}

void SpectrometerAdapter::begin()
{
	motor->setSpeed(maxSpeed);
}

void SpectrometerAdapter::step(int dir)
{
	motor->step(1, dir, SINGLE);
}
