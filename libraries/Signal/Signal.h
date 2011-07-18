#ifndef SIGNAL_H
#define SIGNAL_H

#include <WProgram.h>
#include <stdlib.h>
#include <SignalListener.h>
#include <MedianMeasurement.h>

class Signal {
public:
    Signal(int pin, int listenerSize) : listener(0), median(size), index(0), 
        full(false), smooth(true), pin(pin), listenerSize(listenerSize) 
    {};
    virtual ~Signal() { free(listener); };
    virtual void registerListener(SignalListener *listener);
    virtual void signal();
    virtual void init();
    virtual void useMedian(bool median) { this->smooth = median; }
    
protected:
    virtual void setupMeasurement() {};
    virtual double convert(long) {};
    virtual bool read();

    static const size_t size = 5;
    
    double measurements[size];
    long time[size];
    int index;
    bool full;
    bool smooth;
    
    int pin;    
    
private:
    int listenerSize;
    SignalListener **listener;
    MedianMeasurement median;
    
};

#endif