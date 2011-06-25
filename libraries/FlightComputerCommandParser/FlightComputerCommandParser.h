#ifndef FLIGHT_COMPUTER_COMMAND_PARSER_H
#define FLIGHT_COMPUTER_COMMAND_PARSER_H

#include <FlightComputer.h>
#include <CommandParser.h>

class FlightComputerCommandParser : public CommandParser {
	
public:
	FlightComputerCommandParser(FlightComputer &computer) : computer(computer) {};
	virtual ~FlightComputerCommandParser() {}
	virtual void doCmd(const char *);
	virtual void fail();
	
private:
    
	FlightComputer &computer;
	
};


#endif