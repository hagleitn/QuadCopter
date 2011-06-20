#include <QuadCopter.h>

void QuadCopter::arm() {
	hover(); // neutral state
	adjustGain(0); // initialize gain
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

void QuadCopter::rotate(Direction d, int speed) {
	setSpeed(rudder,d==LEFT?-speed:speed);
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
	left(STOP_SPEED);
	up(STOP_SPEED);
	forward(STOP_SPEED);
	rotate(LEFT, STOP_SPEED);
}

void QuadCopter::setSpeed(Servo &s, int speed) {
	if (speed > MAX_SPEED) {
		speed = MAX_SPEED;
	} else if (speed < STOP_SPEED) {
		speed = STOP_SPEED;
	}
	
	speed = map(speed,-100,100,0,180);
	
	if (speed != s.read()) { 
		s.write(speed);
	}
}