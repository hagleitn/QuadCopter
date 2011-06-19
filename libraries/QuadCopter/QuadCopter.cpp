#include <QuadCopter.h>

void QuadCopter::arm() {
	setSpeed(aileron, 90); 
	setSpeed(rudder, 90); 
	setSpeed(throttle, 90); 
	setSpeed(elevator, 90); 
	setSpeed(gain, 90); 
}

void QuadCopter::attach() {
	aileron.attach(aileronPin); 
	rudder.attach(rudderPin); 
	throttle.attach(throttlePin); 
	elevator.attach(elevatorPin); 
	gain.attach(gainPin);
}

void QuadCopter::init() {
	attach();
	arm();
}

void QuadCopter::left(int speed) {
	setSpeed(aileron,-speed);
}

void QuadCopter::right(int speed) {
	setSpeed(aileron,speed);
}

void QuadCopter::up(int speed) {
	setSpeed(throttle,speed);
}

void QuadCopter::down(int speed) {
	setSpeed(throttle,-speed);
}

void QuadCopter::forward(int speed) {
	setSpeed(elevator,speed);
}

void QuadCopter::backward(int speed) {
	setSpeed(elevator,-speed);
}

void QuadCopter::adjustGain(int gainVal) {
	setSpeed(gain,gainVal);
}

void QuadCopter::hover() {
	left(0);
	up(0);
	forward(0);
}

void QuadCopter::setSpeed(Servo &s, int speed) {
	if (speed > MAX_SPEED) {
		speed = MAX_SPEED;
	} else if (speed < MIN_SPEED) {
		speed = MIN_SPEED;
	}
	
	speed = map(speed,-100,100,0,180);
	
	if (speed != s.read()) { 
		s.write(speed);
	}
}