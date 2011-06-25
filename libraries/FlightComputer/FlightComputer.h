#ifndef FLIGHT_COMPUTER_H
#define FLIGHT_COMPUTER_H

#include <WProgram.h>
#include <QuadCopter.h>
#include <DistanceListener.h>

class FlightComputer : public DistanceListener {
public:
    
    FlightComputer(QuadCopter& ufo) : ufo(ufo) {};
    ~FlightComputer() {}
    void init();
    void takeoff(int);
    void hover(int);
    void land();
    void abort();
    void update(long, long, int);
    void adjust();
    
private:
    QuadCopter &ufo;
    long height;
    long speed;
    int delay;
    
};

#endif
