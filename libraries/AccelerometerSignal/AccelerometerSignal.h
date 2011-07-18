#ifndef ACCELEROMETER_SIGNAL_H
#define ACCELEROMETER_SIGNAL_H

#include <WProgram.h>
#include <stdlib.h>
#include <SignalListener.h>
#include <Signal.h>
#include <MedianMeasurement.h>

class AccelerometerSignal : public Signal {

public:
    AccelerometerSignal(int inPin, int listenerSize) : Signal(inPin, listenerSize) {};
    virtual ~AccelerometerSignal(){}
    
protected:
    virtual double convert(long microseconds) { return ((microseconds / 10) - 500) * 8; };
};

#endif