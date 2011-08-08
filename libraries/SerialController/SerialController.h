#ifndef SERIAL_CONTROLLER_H
#define SERIAL_CONTROLLER_H

#include <WProgram.h>
#include <Tokenizer.h>
class CommandParser;

class SerialController {
    
public:
    
    SerialController(CommandParser &parser, Reader &r) : 
      parser(parser), token(';', r), sleepTime(0), startSleep(0) {}
    ~SerialController() {}
    void init() { token.init(); }
    void executeCommand();
    
private:
    
    void doCmd(const char *);
    void fail();
    
    CommandParser &parser;
    Tokenizer token;
    long sleepTime;
    long startSleep;
};

#endif
