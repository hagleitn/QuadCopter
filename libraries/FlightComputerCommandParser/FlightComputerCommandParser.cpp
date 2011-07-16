#include <FlightComputer.h>
#include <FlightComputerCommandParser.h>

void FlightComputerCommandParser::fail() {
    // aborting flight is too agressive - just ignore failures.
    // computer.emergencyDescent();
}

void FlightComputerCommandParser::doCmd(const char *cmd) {
    
    int x,ret;
    
    switch(cmd[0]) {
        // Command "H <int>" hovers the thing at altitude <int>
        case 'h':
        case 'H':
            ret = sscanf(&cmd[2],"%d", &x);
            if (1 != ret) { fail(); }
            computer.hover(x);
            break;
			
        // Command "T <int>" takeoff and start hovering at <int>
        case 't':
        case 'T':
            ret = sscanf(&cmd[2],"%d",&x);
            if (1 != ret) { fail(); }
            computer.takeoff(x);
            break;
			
        // Command "L" lands the thing
        case 'l':
        case 'L':
            computer.land();
            break;
        
        // Commands "S" and "X" stop the thing
        case 's':
        case 'S':
        case 'x':
        case 'X':
        default:
            computer.abort();
            break;
    }
}
