#ifndef ULTRA_SOUND_SIGNAL_H
#define ULTRA_SOUND_SIGNAL_H

#include <WProgram.h>
#include <stdlib.h>
#include <Signal.h>
#include <SignalListener.h>
#include <MedianMeasurement.h>

class UltraSoundSignal : public Signal {
public:
    UltraSoundSignal(int pingPin, int listenerSize) : Signal(pingPin, listenerSize) {};
    virtual ~UltraSoundSignal(){};
    static const int MAX_RELIABLE = 367;

private:
    virtual void setupMeasurement();
    virtual double convert(long);
};

#endif