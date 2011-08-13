#include <RemoteControl.h>

RemoteControl::RemoteControl(QuadCopter& ufo, int aileronPin, int rudderPin, int throttlePin, int elevatorPin, int gainPin) : ufo(ufo) {
    pins[0] = elevatorPin;   // Red 
    pins[1] = aileronPin;    // White 
    pins[2] = throttlePin;   // Orange 
    pins[3] = rudderPin;     // Yellow 
    this->gainPin = gainPin; // Green (Gain/Gear) 
    controlMask = FULL_MANUAL; // control everything
}
    
void RemoteControl::init() {
    for (int i = 0; i < QuadCopter::DEGREES_OF_FREEDOM; ++i) {
        pinMode(pins[i], INPUT);
    }
    pinMode(gainPin, INPUT);
    arm(false);
}

void RemoteControl::arm(bool arm) {
    armed = arm;
}

void RemoteControl::update() {
    if (controlMask == FULL_MANUAL || isEngaged()) {
        controlMask = FULL_MANUAL;
    }

    char mask = 0x01;
    for (int i = 0; i < QuadCopter::DEGREES_OF_FREEDOM; ++i) {
        if (controlMask & mask) {
            int value = pulseIn(pins[i],HIGH,TIMEOUT);
            ufo.writeRaw((QuadCopter::Direction)i,value);
        }
        mask = mask << 1;
    }
}

bool RemoteControl::isEngaged() {
    int value = pulseIn(pins[QuadCopter::VERTICAL],HIGH,TIMEOUT);
    if (armed) {
        int vertical = ufo.readRaw(QuadCopter::VERTICAL);
        return value > THROTTLE_MIN && (value+THROTTLE_DELTA) > vertical;
    } else {
        if (value < THROTTLE_MIN) {
            arm(true);
        }
        return false;
    }
}
