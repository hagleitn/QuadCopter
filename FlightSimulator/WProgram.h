#ifndef W_PROGRAM_H
#define W_PROGRAM_H
#include <cctype>
#include <cstdlib>
#include <string>
#include <HardwareSerial.h>

#define BIN 1
#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1

void loop(void);
void setup(void);
void init();
long millis();
int map(int val, int srcMin, int srcMax, int dstMin, int dstMax);
int pulseIn(int pin, int mode, int time=0);
void pinMode(int pin, int mode);
void delayMicroseconds(long val);
void digitalWrite(int pin, int value);

#endif
