#ifndef FLIGHT_COMPUTER_H
#define FLIGHT_COMPUTER_H

#include <WProgram.h>
#include <QuadCopter.h>
#include <DistanceListener.h>

class FlightComputer : public DistanceListener {
public:
    
    FlightComputer(QuadCopter& ufo) : ufo(ufo), height(0), speed(0), time(0), lastTime(0), 
    goalSpeed(0), goalHeight(0), lastChange(0), curThrottle(QuadCopter::MIN_SPEED), minDelta(1000) {};
    ~FlightComputer() {}
    void init();
    void takeoff(int);
    void hover(int);
    void land();
    void abort();
    void update(long, long, long);
    void adjust();
    
private:
    QuadCopter &ufo;
    long height;
    long speed;
    long goalSpeed;
    long goalHeight;
    long lastChange;
    long curThrottle;
    long time;
    long minDelta;
    long lastTime; // debugging
    
};

#endif
