#include <Servo.h>
#include <WProgram.h>
#include <iostream>

using namespace std;

const int throttlePin = 10;

void Servo::attach(int value) {
	pin = value;
}

void Servo::write(int value) {
	if (pin == throttlePin) {
		throttle(map(value,0,180,-100,100));
	}
	this->value = map(value,0,180,600,2400);
}

void Servo::writeMicroseconds(int value) {
	if (pin == throttlePin) {
		throttle(map(value,600,2400,-100,100));
	}
	this->value = value;
}

int Servo::read() {
	return map(value,600,2400,0,180);
}

int Servo::readMicroseconds() {
	return value;
}
