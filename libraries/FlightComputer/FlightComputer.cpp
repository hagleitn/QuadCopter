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


