#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

class CommandParser {
    
public:
    
	virtual void doCmd(const char *) = 0;
	virtual void fail() = 0;
	
};


#endif