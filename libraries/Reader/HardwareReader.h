#ifndef HARDWARE_READER_H
#define HARDWARE_READER_H

#include <Reader.h>
#include <HardwareReader.h>

class HardwareReader : public Reader {
public:
    HardwareReader(HardwareSerial &serial) : serial(serial) {}
    virtual ~HardwareReader() {}
    virtual int available() { return serial.available(); }
    virtual char read() { return serial.read(); }
private:
    HardwareSerial &serial;
};

#endif