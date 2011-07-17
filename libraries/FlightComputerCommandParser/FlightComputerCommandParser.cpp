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
            if (1 != ret) { fail(); return; }
            computer.hover(x);
            break;
			
        // Command "T <int>" takeoff and start hovering at <int>
        case 't':
        case 'T':
            ret = sscanf(&cmd[2],"%d",&x);
            if (1 != ret) { fail(); return; }
            computer.takeoff(x);
            break;
			
        // Command "L" lands the thing
        case 'l':
        case 'L':
            computer.land();
            break;
            
        // Command "S" turns on/off stabilization
        case 's':
        case 'S':
            ret = sscanf(&cmd[2],"%d",&x);
            if (1 != ret) { fail(); return; }
            computer.stabilize(x==0?false:true);
            break;
        
        // Commands "X" stops the thing
        case 'x':
        case 'X':
        default:
            computer.abort();
            break;
    }
}
