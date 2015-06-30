#include <Arduino.h>

static uint8_t pmode[NUM_DIGITAL_PINS];
static uint8_t pvalueIn[NUM_DIGITAL_PINS];
static uint8_t pvalueOut[NUM_DIGITAL_PINS];

void pinInit(void)
{
	for(int i = 0; i < NUM_DIGITAL_PINS; i++) {
		pmode[i] = INPUT;
		pvalueIn[i] = LOW;
		pvalueOut[i] = LOW;
	}
}

void pinMode(uint8_t pin, uint8_t mode)
{
	pmode[pin] = mode;
}

uint8_t pinMode_Get(uint8_t pin)
{
	return pmode[pin];
}

int digitalRead(uint8_t pin)
{
	if(pmode[pin] == INPUT)
		return pvalueIn[pin];
	else
		return pvalueOut[pin];
}

void digitalRead_Set(uint8_t pin, uint8_t val)
{
	pvalueIn[pin] = val;
}

void digitalWrite(uint8_t pin, uint8_t val)
{
	pvalueOut[pin] = val;
}
