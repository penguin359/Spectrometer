#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

//void yield(void);

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);
//int analogRead(uint8_t);
//void analogReference(uint8_t mode);
//void analogWrite(uint8_t, int);

//unsigned long millis(void);
//unsigned long micros(void);
//void delay(unsigned long);
//void delayMicroseconds(unsigned int us);
//unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);

//void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
//uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);

//void attachInterrupt(uint8_t, void (*)(void), int mode);
//void detachInterrupt(uint8_t);

//void setup(void);
//void loop(void);

/* Mocks following */
uint8_t pinMode_Get(uint8_t pin);
void pinInit(void);
void digitalRead_Set(uint8_t pin, uint8_t value);

#ifdef __cplusplus
} // extern "C"
#endif

/* include pins_arduino.h */
#define NUM_DIGITAL_PINS            20
#define NUM_ANALOG_INPUTS           6
