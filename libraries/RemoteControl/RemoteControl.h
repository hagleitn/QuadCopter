#ifndef REMOTE_CONTROL_H
#define REMOTE_CONTROL_H

#include <WProgram.h>
#include <QuadCopter.h>

class RemoteControl {
public:
    
    static const char FULL_MANUAL = 0xff;
    
    RemoteControl(QuadCopter& ufo, int aileronPin, int rudderPin, int throttlePin, int elevatorPin, int gainPin);
    ~RemoteControl() {}
    void init();
    void update();
    void setControlMask(char mask) { controlMask = mask; }
    char getControlMask() { return controlMask; }
    
private:
    
    static const int THROTTLE_MIN = 100; // min raw value from pulse in to take over
    char controlMask; // all bits set means manual control for the particular servo
    int pins[QuadCopter::DEGREES_OF_FREEDOM];
    int gainPin;
    QuadCopter &ufo;
    
    bool isEngaged();
};

#endif
