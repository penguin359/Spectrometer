#include "config.h"
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
	long diffWavelengthInSteps = currentWavelengthInSteps -
				     newWavelengthInSteps;
	int dir;
	long i;
	bool lowLimitHit = false;
	bool highLimitHit = false;

	if(diffWavelengthInSteps > 0) {
		//myMotor->step(diffWavelengthInSteps, FORWARD, SINGLE);
		dir = FORWARD;
	} else {
		//myMotor->step(-diffWavelengthInSteps, BACKWARD, SINGLE);
		dir = BACKWARD;
		diffWavelengthInSteps = -diffWavelengthInSteps;
	}

	for(i = 0; i < diffWavelengthInSteps; i++) {
		if(digitalRead(LOW_LIMIT_SWITCH_PIN)) {
			if(!lowLimitHit)
				Serial.println(F("Low Limit Hit"));
			lowLimitHit = true;
		} else if(lowLimitHit) {
			Serial.println(F("Low Limit Released"));
			lowLimitHit = false;
		}

		if(digitalRead(HIGH_LIMIT_SWITCH_PIN)) {
			if(!highLimitHit)
				Serial.println(F("High Limit Hit"));
			highLimitHit = true;
		} else if(highLimitHit) {
			Serial.println(F("High Limit Released"));
			highLimitHit = false;
		}

#if 1
		if((dir == BACKWARD && lowLimitHit) || (dir == FORWARD && highLimitHit))
			break;
#endif

		myMotor->step(1, dir, SINGLE);
	}

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
