#ifndef REMOTE_CONTROL_H
#define REMOTE_CONTROL_H

#include <WProgram.h>
#include <QuadCopter.h>

class RemoteControl {
public:
    
    RemoteControl(QuadCopter& ufo, int aileronPin, int rudderPin, int throttlePin, int elevatorPin, int gainPin);
    ~RemoteControl() {}
    void init();
    void update();
    bool isEngaged();
    
private:
    
    static const int THROTTLE_MIN = 100;
    
    int pins[QuadCopter::DEGREES_OF_FREEDOM];
    int gainPin;
    QuadCopter &ufo;    
};

#endif
