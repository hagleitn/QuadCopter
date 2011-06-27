#ifndef SERIAL_CONTROLLER_H
#define SERIAL_CONTROLLER_H

#include <WProgram.h>
#include <Tokenizer.h>
class CommandParser;

class SerialController {
    
public:
    
    SerialController(CommandParser &parser, int killPin, Reader &r) : 
      parser(parser), token(';', r), lastValueKillPin(HIGH), killPin(killPin), sleepTime(0), startSleep(0) {}
    ~SerialController() {}
    void init() { token.init(); pinMode(killPin, INPUT); }
    void executeCommand();
    
private:
    
    void doCmd(const char *);
    void fail();
    
    CommandParser &parser;
    Tokenizer token;
    int killPin;
    int lastValueKillPin;
    long sleepTime;
    long startSleep;
};

#endif
