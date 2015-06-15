#include "Spectrometer.h"


Spectrometer::Spectrometer(Adafruit_StepperMotor *newMotor) : currentWavelengthInSteps(0)
{
	myMotor = newMotor;
}

void Spectrometer::begin()
{
	/* XXX Hardware specific */
	//AFMS.begin();
	myMotor->setSpeed(150); // 10 rpm
}

long Spectrometer::getStepToRealRatio()
{
	return stepToRealRatio;
}

long Spectrometer::getRealWavelength()
{
	return currentWavelengthInSteps/stepToRealRatio;
}

long Spectrometer::getRealWavelengthFrac()
{
	return currentWavelengthInSteps%stepToRealRatio;
}

long Spectrometer::getDisplayedWavelength()
{
	return currentWavelengthInSteps/stepToDisplayedRatio;
}

void Spectrometer::setDisplayedWavelength(long wavelength)
{
	currentWavelengthInSteps = wavelength*stepToDisplayedRatio;
}

void Spectrometer::moveTo(long wavelength)
{
	long newWavelengthInSteps = wavelength*stepToRealRatio;
	long diffWavelengthInSteps = newWavelengthInSteps -
				     currentWavelengthInSteps;
	int dir;

	if(diffWavelengthInSteps > 0) {
		//myMotor->step(diffWavelengthInSteps, FORWARD, SINGLE);
		dir = FORWARD;
	} else {
		//myMotor->step(-diffWavelengthInSteps, BACKWARD, SINGLE);
		dir = BACKWARD;
		diffWavelengthInSteps = -diffWavelengthInSteps;
	}

	myMotor->step(diffWavelengthInSteps, dir, SINGLE);
	currentWavelengthInSteps = newWavelengthInSteps;
}

void Spectrometer::up()
{
	moveTo(currentWavelengthInSteps + 1);
}

void Spectrometer::down()
{
	moveTo(currentWavelengthInSteps - 1);
}
