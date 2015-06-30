#ifndef _SPECTROMETER_ADAPTER_H_
#define _SPECTROMETER_ADAPTER_H_


#include <Adafruit_MotorShield.h>


class SpectrometerAdapter {
	Adafruit_StepperMotor *motor;
	const uint8_t lowLimitPin;
	const uint8_t highLimitPin;

    public:
	static const uint16_t maxSpeed = 150;

	SpectrometerAdapter(Adafruit_StepperMotor *newMotor,
			    uint8_t newLowLimitPin,
			    uint8_t newHighLimitPin);
	void begin();
	void step(int dir);
	uint8_t lowLimitHit();
	uint8_t highLimitHit();
};


#endif /* _SPECTROMETER_ADAPTER_H_ */
