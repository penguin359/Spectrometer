#ifndef _SPECTROMETER_ADAPTER_H_
#define _SPECTROMETER_ADAPTER_H_


#include <Adafruit_MotorShield.h>


class SpectrometerAdapter {
	Adafruit_StepperMotor *motor;

    public:
	static const uint16_t maxSpeed = 150;

	SpectrometerAdapter(Adafruit_StepperMotor *newMotor);
	void begin();
	void step(int dir);
};


#endif /* _SPECTROMETER_ADAPTER_H_ */
