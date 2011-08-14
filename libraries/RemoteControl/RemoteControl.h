#ifndef REMOTE_CONTROL_H
#define REMOTE_CONTROL_H

#include <WProgram.h>
#include <QuadCopter.h>

class RemoteControl {
public:
    
    static const char FULL_MANUAL    = 0xff;
    static const char ELEVATOR_MASK  = 0x01;
    static const char AILERON_MASK   = 0x02;
    static const char THROTTLE_MASK  = 0x04;
    static const char RUDDER_MASK    = 0x08;
    static const int  TIMEOUT        = 20000;
    
    RemoteControl(QuadCopter& ufo, int aileronPin, int rudderPin, int throttlePin, int elevatorPin, int gainPin);
    ~RemoteControl() {}
    void init();
    void update();
    void arm(bool);
    void setControlMask(char mask) { controlMask = mask; }
    char getControlMask() { return controlMask; }
    
private:
    
    static const int THROTTLE_MIN = 1300; // min raw value from pulse in to take over
    static const int THROTTLE_DELTA = 200; // if manual throttle comes that close to current setting take over
    char controlMask; // all bits set means manual control for the particular servo
    int pins[QuadCopter::DEGREES_OF_FREEDOM];
    int gainPin;
    bool armed;
    QuadCopter &ufo;
    
    bool isEngaged();
};

#endif
