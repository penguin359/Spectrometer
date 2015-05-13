#define	LOW_LIMIT_SWITCH_PIN	4
#define HIGH_LIMIT_SWITCH_PIN	5
#define STEP_PIN		3
#define DIRECTION_PIN		2


void setup()
{
	Serial.begin(9600);

	pinMode(LOW_LIMIT_SWITCH_PIN, INPUT);
	pinMode(HIGH_LIMIT_SWITCH_PIN, INPUT);
	digitalWrite(LOW_LIMIT_SWITCH_PIN, HIGH);
	digitalWrite(HIGH_LIMIT_SWITCH_PIN, HIGH);

	pinMode(STEP_PIN, OUTPUT);
	pinMode(DIRECTION_PIN, OUTPUT);

	Serial.println("Start-up complete.");
}

bool lowLimitHit = false;
bool highLimitHit = false;

#define STEPS_PER_COUNT		10

void loop()
{
	int cmd;
	int i;

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

	cmd = Serial.read();

	if(lowLimitHit || highLimitHit)
		return;

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
}
