#ifndef QUAD_COPTER_COMMAND_PARSER_H
#define QUAD_COPTER_COMMAND_PARSER_H

#include <QuadCopter.h>
#include <CommandParser.h>

class QuadCopterCommandParser : public CommandParser {
	
public:
	QuadCopterCommandParser(QuadCopter &ufo) : ufo(ufo) {};
	virtual ~QuadCopterCommandParser() {}
	virtual void doCmd(const char *);
	virtual void fail();
	
private:
    
	QuadCopter &ufo;
	
};


#endif