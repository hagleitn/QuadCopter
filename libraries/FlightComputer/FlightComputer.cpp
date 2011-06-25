#include <FlightComputer.h>

void FlightComputer::init() {
}

void FlightComputer::takeoff(int meters) {
    ufo.throttle(-95);
}

void FlightComputer::hover(int meters) {
    ufo.throttle(-98);
}

void FlightComputer::land() {
    ufo.throttle(0);
}

void FlightComputer::abort() {
    ufo.throttle(0);
}

// receive height, speed
void FlightComputer::update(long height, long speed, int delay) {
    this->height = height;
    this->speed = speed;
    this->delay = delay;
}

// adjust controls to meet goal
void FlightComputer::adjust() {
}

