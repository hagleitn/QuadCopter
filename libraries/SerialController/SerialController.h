#ifndef SERIAL_CONTROLLER_H
#define SERIAL_CONTROLLER_H

#include "WProgram.h"
#include "Tokenizer.h"
#include "QuadCopter.h"

class SerialController {
	
public:
	
	SerialController(QuadCopter ufo, Tokenizer token, int killPin) : 
					ufo(ufo), token(token), killPin(killPin), sleepTime(0), startSleep(0) {}
	~SerialController() {}
	void init() { ufo.init(); token.init(); pinMode(killPin, INPUT); }
	void executeCommand();
	
private:
	
	void doCmd(const char *);
	void fail();
	
	QuadCopter &ufo;
	Tokenizer &token;
	int killPin;
	long sleepTime;
	long startSleep;
};

#endif