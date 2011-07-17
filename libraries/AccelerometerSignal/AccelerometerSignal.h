#ifndef ACCELEROMETER_SIGNAL_H
#define ACCELEROMETER_SIGNAL_H

#include <WProgram.h>
#include <stdlib.h>
#include <SignalListener.h>
#include <MedianMeasurement.h>

class AccelerometerSignal {

public:
    AccelerometerSignal(int inPin, int listenerSize) : listener(0), median(5), index(0), full(false), pin(inPin), listenerSize(listenerSize) {};
    ~AccelerometerSignal(){};
    void registerListener(SignalListener *listener);
    void signal();
    void init();

private:
    bool read();
    double millig(long);
    
    static const size_t size = 5;
    
    int listenerSize;
    SignalListener **listener;
    MedianMeasurement median;
    
    double force[size];
    long time[size];
    int index;
    bool full;
    
    int pin;
};

#endif