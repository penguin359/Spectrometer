#ifndef _SPECTROMETER_ADAPTER_H_
#define _SPECTROMETER_ADAPTER_H_


#include <Adafruit_MotorShield.h>


class SpectrometerAdapter {
    public:
	virtual ~SpectrometerAdapter() {}
	virtual void begin() = 0;
	virtual void step(int dir) = 0;
	virtual uint8_t lowLimitHit() = 0;
	virtual uint8_t highLimitHit() = 0;
};


class AdafruitSpectrometerAdapter : public SpectrometerAdapter {
	Adafruit_StepperMotor *motor;
	const uint8_t lowLimitPin;
	const uint8_t highLimitPin;

    public:
	static const uint16_t maxSpeed = 150;

	AdafruitSpectrometerAdapter(Adafruit_StepperMotor *newMotor,
			    uint8_t newLowLimitPin,
			    uint8_t newHighLimitPin);
	virtual void begin();
	virtual void step(int dir);
	virtual uint8_t lowLimitHit();
	virtual uint8_t highLimitHit();
};


class CounterSpectrometerAdapter : public SpectrometerAdapter {
	int position;
	int lowLimit;
	int highLimit;

    public:
	CounterSpectrometerAdapter(int newLowLimit, int newHighLimit);
	virtual void begin();
	virtual void step(int dir);
	virtual uint8_t lowLimitHit();
	virtual uint8_t highLimitHit();

	int getPosition();
	void setPosition(int position);
	int outOfBounds();
};


#endif /* _SPECTROMETER_ADAPTER_H_ */
