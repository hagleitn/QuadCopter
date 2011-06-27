#include <FlightComputer.h>

void FlightComputer::init() {
}

void FlightComputer::takeoff(int meters) {
    ufo.throttle(-28);
}

void FlightComputer::hover(int meters) {
    ufo.throttle(-10);
}

void FlightComputer::land() {
    ufo.throttle(QuadCopter::MIN_SPEED);
}

void FlightComputer::abort() {
    ufo.throttle(QuadCopter::MIN_SPEED);
}

// receive height, speed
void FlightComputer::update(long height, long speed, long time) {
    this->height = height;
    this->speed = speed;
    this->time = time;
    if (time - lastTime > 1000) {
        Serial.print("height: ");
        Serial.print(this->height);
        Serial.print(" speed: ");
        Serial.print(this->speed);
        Serial.print(" time: ");
        Serial.println(this->time);
	lastTime = time;
    }
}

// adjust controls to meet goal
void FlightComputer::adjust() {
}

