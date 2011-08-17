#include <Servo.h>
#include <WProgram.h>
#include <iostream>

using namespace std;

const int throttlePin = 4;

void Servo::attach(int value) {
    attach(value,0,0);
}

void Servo::attach(int value, int min, int max) {
	pin = value;
}

void Servo::write(int value) {
	if (pin == throttlePin) {
		throttle(map(value,0,180,-100,100));
	}
	this->value = map(value,0,180,1150,1950);
}

void Servo::writeMicroseconds(int value) {
	if (pin == throttlePin) {
		throttle(map(value,1150,1950,-100,100));
	}
	this->value = value;
}

int Servo::read() {
	return map(value,1150,1950,0,180);
}

int Servo::readMicroseconds() {
	return value;
}
