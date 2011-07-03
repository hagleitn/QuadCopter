#include <RemoteControl.h>

RemoteControl::RemoteControl(QuadCopter& ufo, int aileronPin, int rudderPin, int throttlePin, int elevatorPin, int gainPin) : ufo(ufo) {
    pins[0] = elevatorPin;   // Red 
    pins[1] = aileronPin;    // White 
    pins[2] = throttlePin;   // Orange 
    pins[3] = rudderPin;     // Yellow 
    this->gainPin = gainPin; // Green (Gain/Gear) 
}
    
void RemoteControl::init() {
    for (int i = 0; i < QuadCopter::DEGREES_OF_FREEDOM; ++i) {
        pinMode(pins[i], INPUT);
    }
    pinMode(gainPin, INPUT);
}

void RemoteControl::update() {
    for (int i = 0; i < QuadCopter::DEGREES_OF_FREEDOM; ++i) {
        int value = pulseIn(pins[i],HIGH);
        ufo.writeRaw((QuadCopter::Direction)i,value);
    }
}

bool RemoteControl::isEngaged() {
    int vertical = ufo.readRaw(QuadCopter::VERTICAL);
    int value = pulseIn(pins[QuadCopter::VERTICAL],HIGH);
    return value > THROTTLE_MIN && value > vertical;
}