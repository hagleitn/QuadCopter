#ifndef ULTRA_SOUND_SIGNAL_H
#define ULTRA_SOUND_SIGNAL_H

#include <WProgram.h>
#include <stdlib.h>
#include <SignalListener.h>
#include <MedianMeasurement.h>

class UltraSoundSignal {
public:
    UltraSoundSignal(int pingPin, int listenerSize) : listener(0), median(5), /*speed(-1),*/ index(0), full(false), pin(pingPin), listenerSize(listenerSize) {};
    ~UltraSoundSignal(){};
    void registerListener(SignalListener *listener);
    void signal();
    void init();
private:
    bool read();
    double centimeters(long);
    // bool computeSpeed();
    
    static const size_t size = 5;
    static const double MAX_RELIABLE = 20*100; // 20 meters
    // static const long MIN_TIME_FOR_SPEED = 300; // 300 milliseconds
    
    int listenerSize;
    SignalListener **listener;
    MedianMeasurement median;
    
    double distance[size];
    long time[size];
    int index;
    bool full;
    
    // double speed;
    
    int pin;
};

#endif