#ifndef FLIGHT_COMPUTER_H
#define FLIGHT_COMPUTER_H

#include <WProgram.h>
#include <QuadCopter.h>

class FlightComputer {
public:
    
    FlightComputer(QuadCopter& ufo) : ufo(ufo) {};
    ~FlightComputer() {}
    void init();
    void takeoff(int);
    void hover(int);
    void land();
    void abort();
    
private:
    QuadCopter &ufo;
};

#endif
