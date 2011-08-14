#include <Servo.h>
#include <WProgram.h>
#include <iostream>

const int throttlePin = 10;

void Servo::attach(int value) {
	pin = value;
}

void Servo::write(int value) {
	if (pin == throttlePin) {
		throttle(map(value,0,180,-100,100));
	}
}

void Servo::writeMicroseconds(int value) {
}

int Servo::read() {
	return -1;
}

int Servo::readMicroseconds() {
	return 0;
}
