#ifndef SOFTWARE_READER_H
#define SOFTWARE_READER_H

#include <Reader.h>
#include <SoftwareSerial.h>

class SoftwareReader : public Reader {
public:
    SoftwareReader(SoftwareSerial &serial) : serial(serial) {}
    virtual ~SoftwareReader() {}
    virtual int available() { return serial.available(); }
    virtual char read() { return serial.read(); }
private:
    SoftwareSerial &serial;
};

#endif