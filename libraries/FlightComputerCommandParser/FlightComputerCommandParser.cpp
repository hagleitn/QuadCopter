#include <FlightComputer.h>
#include <FlightComputerCommandParser.h>
#include <AutoControl.h>

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
        
        case 'C':
        case 'c':
            {
                int type;
                
                double proportional;
                double integral;
                double derivative;
                double min;
                double max;
                char *p = const_cast<char*>(cmd) + 2;
                
                type = strtol(p,&p,10);
                proportional = strtod(p,&p);
                integral = strtod(p,&p);
                derivative = strtod(p,&p);
                min = strtod(p,&p);
                max = strtod(p,&p);
                
                AutoControl::Configuration conf = {proportional,integral,derivative,min,max};
                switch (type) {
                    case 1:
                        computer.setHoverConfiguration(conf);
                        break;
                    case 2:
                        computer.setLandingConfiguration(conf);
                        break;
                    case 3:
                        computer.setStabilizerConfiguration(conf);
                        break;
                    default:
                        fail();
                        break;
                }
            }
            break;
        
        // (Re-)Engage auto throttle
        case 'e':
        case 'E':
            computer.autoControl();
            break;
            
        // Command "S" turns on/off stabilization
        case 's':
        case 'S':
            ret = sscanf(&cmd[2],"%d",&x);
            if (1 != ret) { fail(); return; }
            computer.stabilize(x==0?false:true);
            break;

        // Set minimum throttle
        case 'm':
        case 'M':
            ret = sscanf(&cmd[2],"%d",&x);
            if (1 != ret) { fail(); return; }
            computer.setMinThrottle(x);
            break;
        
        // Set maximum throttle
        case 'n':
        case 'N':
            ret = sscanf(&cmd[2],"%d",&x);
            if (1 != ret) { fail(); return; }
            computer.setMaxThrottle(x);
            break;
        
        // Commands "X" stops the thing
        case 'x':
        case 'X':
            computer.abort();
            break;
        default:
            fail();
            break;
    }
}
