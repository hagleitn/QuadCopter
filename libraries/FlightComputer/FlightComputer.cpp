#include <FlightComputer.h>

void FlightComputer::init() {
}

void FlightComputer::takeoff(int meters) {
  goalHeight = meters;
  goalSpeed = 5;
}

void FlightComputer::hover(int meters) {
    ufo.throttle(-10);
}

void FlightComputer::land() {
    ufo.throttle(QuadCopter::MIN_SPEED);
    curThrottle = QuadCopter::MIN_SPEED;
    goalHeight = 0;
    goalSpeed = -1;
}

void FlightComputer::abort() {
    ufo.throttle(QuadCopter::MIN_SPEED);
    curThrottle = QuadCopter::MIN_SPEED;
    goalHeight = 0;
    goalSpeed = 0;
}

// receive height, speed
void FlightComputer::update(double height) {
    this->height = height;
    this->time = millis();
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
    if (override) {
        rc.update();
    } else if (rc.isEngaged()) {
        override = true;
    } else {
        if (time - lastChange > minDelta) {
            if (goalHeight < height) {
                land();
            } else if (speed < goalSpeed && curThrottle < 30) {
                curThrottle += 10;
                Serial.print("Throttle: ");
                Serial.println(curThrottle);
                ufo.throttle(curThrottle);
            }
            lastChange = time;
        }
    }
}

