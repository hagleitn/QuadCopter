#ifndef ULTRA_SOUND_SIGNAL_H
#define ULTRA_SOUND_SIGNAL_H

#include <WProgram.h>
#include <stdlib.h>
#include <DistanceListener.h>
#include <MedianMeasurement.h>

class UltraSoundSignal {
public:
    UltraSoundSignal(int pingPin) : listener(0), median(5), speed(-1), index(0), full(false), pin(pingPin) {};
    ~UltraSoundSignal(){};
    void registerListener(DistanceListener *listener);
    void signal();
    void init() {median.init();};
private:
    bool read();
    long centimeters(long);
    bool computeSpeed();
    
    static const size_t size = 5;
    static const long MAX_RELIABLE = 20*100; // 20 meters
    static const long MIN_TIME_FOR_SPEED = 300; // 300 milliseconds
    
    DistanceListener *listener;
    MedianMeasurement median;
    
    long distance[size];
    long time[size];
    int index;
    bool full;
    
    long speed;
    
    int pin;
};

#endif