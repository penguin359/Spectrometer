#ifndef _SPECTROMETER_H_
#define _SPECTROMETER_H_


#include "Adafruit_MotorShield.h"


class Spectrometer {
	/* The wavelength displayed on the Spectrometer has
	 * about a 1.5 ratio to the actual wavelength selected.
	 * These constants are the ratio of displayed or real
	 * wavelength to the number of steps to drive the stepper
	 * motor moving the mirrors. Specifically, it's the number
	 * of steps needed to move one wavelength.
	 */
	//const long stepToDisplayedRatio = 2;	/* Wavelength shown on meter */
	//const long stepToRealRatio = 3;		/* Actual light wavelength */
	static const long stepToDisplayedRatio = 1;	/* Wavelength shown on meter */
	static const long stepToRealRatio = 1;		/* Actual light wavelength */

	long currentWavelengthInSteps;

	Adafruit_StepperMotor *myMotor;

    public:
	Spectrometer(Adafruit_StepperMotor *newMotor);
	void begin();
	long getStepToRealRatio();
	long getRealWavelength();
	long getRealWavelengthFrac();
	long getDisplayedWavelength();
	void setDisplayedWavelength(long wavelength);
	void moveTo(long wavelength);
	void up();
	void down();
};


#endif /* _SPECTROMETER_H_ */
