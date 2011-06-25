#ifndef ULTRA_SOUND_SIGNAL_H
#define ULTRA_SOUND_SIGNAL_H

#include <WProgram.h>
#include <DistanceListener.h>

class UltraSoundSignal {
public:
    UltraSoundSignal(int pingPin) : listener(0), distance(0), speed(0), delay(0), pin(pingPin) {};
    ~UltraSoundSignal(){};
    long read();
    void registerListener(DistanceListener *listener);
    void signal();
private:
    long centimeters(long);
    
    DistanceListener *listener;
    long oldDistance;
    long oldTime;
    long distance;
    long time;
    long speed;
    int delay;
    int pin;
};

#endif