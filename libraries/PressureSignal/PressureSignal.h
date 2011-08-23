#ifndef ACCELEROMETER_SIGNAL_H
#define ACCELEROMETER_SIGNAL_H

#include <WProgram.h>
#include <stdlib.h>
#include <SignalListener.h>
#include <Signal.h>

class PressureSignal : public Signal {

public:
    PressureSignal(int dataReadyPin, int chipSelectPin, int listenerSize) : Signal(dataReadyPin, listenerSize), 
        dataReadyPin(dataReadyPin), chipSelectPin(chipSelectPin) {};
    virtual ~PressureSignal(){}
    virtual void init();
    
protected:
    virtual long measure();
    virtual bool convert(long, double&);
    
private:
    unsigned int readRegister(byte, int);
    void writeRegister(byte, byte);

    static const int PRESSURE = 0x1F;      //3 most significant bits of pressure
    static const int PRESSURE_LSB = 0x20;  //16 least significant bits of pressure
    static const byte READ = 0b11111100;     // SCP1000's read command
    static const byte WRITE = 0b00000010;   // SCP1000's write command
    
    int dataReadyPin;
    int chipSelectPin;
    
};

#endif
