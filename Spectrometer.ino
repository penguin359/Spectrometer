#include <Wire.h>
#include <Adafruit_MotorShield.h>

#define	LOW_LIMIT_SWITCH_PIN	2
#define HIGH_LIMIT_SWITCH_PIN	3
#define STEP_PIN		4
#define DIRECTION_PIN		5


Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 1);

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
	const long stepToDisplayedRatio = 1;	/* Wavelength shown on meter */
	const long stepToRealRatio = 1;		/* Actual light wavelength */

	long currentWavelengthInSteps = 0;

    public:
	void begin() {
		/* XXX Hardware specific */
		AFMS.begin();
		myMotor->setSpeed(10); // 10 rpm
	}

	long getRealWavelength() {
		return currentWavelengthInSteps/stepToRealRatio;
	}

	long getDisplayedWavelength() {
		return currentWavelengthInSteps/stepToDisplayedRatio;
	}

	void setDisplayedWavelength(long wavelength) {
		currentWavelengthInSteps = wavelength*stepToDisplayedRatio;
	}

	void moveTo(long wavelength) {
		long newWavelengthInSteps = wavelength*stepToRealRatio;
		long diffWavelengthInSteps = currentWavelengthInSteps -
					     newWavelengthInSteps;

		if(diffWavelengthInSteps > 0) {
			myMotor->step(diffWavelengthInSteps, FORWARD, SINGLE);
		} else {
			myMotor->step(-diffWavelengthInSteps, BACKWARD, SINGLE);
		}

		currentWavelengthInSteps = newWavelengthInSteps;
	}

	void up() {
		moveTo(currentWavelengthInSteps + 1);
	}

	void down() {
		moveTo(currentWavelengthInSteps - 1);
	}
};

class DummySpectrometer {
	/* The wavelength displayed on the Spectrometer has
	 * about a 1.5 ratio to the actual wavelength selected.
	 * These constants are the ratio of displayed or real
	 * wavelength to the number of steps to drive the stepper
	 * motor moving the mirrors. Specifically, it's the number
	 * of steps needed to move one wavelength.
	 */
	//const long stepToDisplayedRatio = 2;	/* Wavelength shown on meter */
	//const long stepToRealRatio = 3;		/* Actual light wavelength */
	const long stepToDisplayedRatio = 1;	/* Wavelength shown on meter */
	const long stepToRealRatio = 1;		/* Actual light wavelength */

	long currentWavelengthInSteps = 0;

    public:
	void begin() {
		/* XXX Hardware specific */
	}

	long getRealWavelength() {
		return currentWavelengthInSteps/stepToRealRatio;
	}

	long getDisplayedWavelength() {
		return currentWavelengthInSteps/stepToDisplayedRatio;
	}

	void setDisplayedWavelength(long wavelength) {
		currentWavelengthInSteps = wavelength*stepToDisplayedRatio;
		Serial.print("Setting displayed wavelength to ");
		Serial.println(currentWavelengthInSteps);
	}

	void moveTo(long wavelength) {
		long newWavelengthInSteps = wavelength*stepToRealRatio;
		long diffWavelengthInSteps = currentWavelengthInSteps -
					     newWavelengthInSteps;

		if(diffWavelengthInSteps > 0) {
			Serial.print("Moving FORWARD by ");
			Serial.println(diffWavelengthInSteps);
		} else {
			Serial.print("Moving BACKWARD by ");
			Serial.println(-diffWavelengthInSteps);
		}

		currentWavelengthInSteps = newWavelengthInSteps;
	}

	void up() {
		moveTo(currentWavelengthInSteps + 1);
	}

	void down() {
		moveTo(currentWavelengthInSteps - 1);
	}
};


Spectrometer spectrometer;
//DummySpectrometer spectrometer;

void getCmd()
{
	static int init = 0;
	static int cmd = -1;
	long wavelength;

	//Serial.println("getCmd()");
	if(cmd >= 0 || !init) {
		init = 1;
		Serial.println();
		Serial.println();
		Serial.print("Current wavelength: ");
		Serial.println(spectrometer.getRealWavelength());
		Serial.print("Displayed wavelength: ");
		Serial.println(spectrometer.getDisplayedWavelength());
		Serial.println();
		Serial.println("Set displayed wavelength");
		Serial.println("Go to wavelength");
		Serial.println("Up one wavelength");
		Serial.println("Down one wavelength");
		Serial.println();
	}

	cmd = Serial.read();

	switch(cmd) {
		case 's':
		case 'S':
			Serial.print("Wavelength: ");
			wavelength = Serial.parseInt();
			spectrometer.setDisplayedWavelength(wavelength);
			break;

		case 'g':
		case 'G':
			Serial.print("Wavelength: ");
			wavelength = Serial.parseInt();
			spectrometer.moveTo(wavelength);
			break;

		case 'u':
		case 'U':
			spectrometer.up();
			break;

		case 'd':
		case 'D':
			spectrometer.down();
			break;

		default:
			break;
	}
}

void setup()
{
	Serial.begin(9600);;

	pinMode(LOW_LIMIT_SWITCH_PIN, INPUT);
	pinMode(HIGH_LIMIT_SWITCH_PIN, INPUT);
	digitalWrite(LOW_LIMIT_SWITCH_PIN, HIGH);
	digitalWrite(HIGH_LIMIT_SWITCH_PIN, HIGH);

	pinMode(STEP_PIN, OUTPUT);
	pinMode(DIRECTION_PIN, OUTPUT);

	spectrometer.begin();

	Serial.println("Start-up complete.");
}

bool lowLimitHit = false;
bool highLimitHit = false;

#define STEPS_PER_COUNT		10

void loop()
{
	int cmd;
	int i;

#if 1
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

	if(lowLimitHit || highLimitHit)
		return;
#endif

	//cmd = Serial.read();
	myMotor->step(10, FORWARD, SINGLE);
	getCmd();

#if 0
	switch(cmd) {
		case 'u':
		case 'U':
			Serial.println("Up");
			digitalWrite(DIRECTION_PIN, LOW);
			for(i = 0; i < STEPS_PER_COUNT; i++) {
				digitalWrite(STEP_PIN, HIGH);
				delay(5);
				digitalWrite(STEP_PIN, LOW);
				delay(5);
			}
			break;

		case 'd':
		case 'D':
			Serial.println("Down");
			digitalWrite(DIRECTION_PIN, HIGH);
			for(i = 0; i < STEPS_PER_COUNT; i++) {
				digitalWrite(STEP_PIN, HIGH);
				delay(5);
				digitalWrite(STEP_PIN, LOW);
				delay(5);
			}
			break;

		default:
			break;
	}
#endif
}
