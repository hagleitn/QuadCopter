#include <QuadCopter.h>
#include <QuadCopterCommandParser.h>

void QuadCopterCommandParser::fail() {
    ufo.stop();
    ufo.throttle(QuadCopter::MIN_SPEED);
}

void QuadCopterCommandParser::doCmd(const char *cmd) {
    
    int x,y,z,r,ret;
    
    switch(cmd[0]) {
			// Command "M <int>, <int>, <int>, <int>" will set all 4 speeds at once
        case 'm':
        case 'M':
            ret = sscanf(&cmd[2],"%d, %d, %d, %d", &x,&y,&z,&r);
            if (4 != ret) { fail(); }
            ufo.move(x,y,z,r);
            break;
			
			// Command "T <int>" sets the throttle
        case 't':
        case 'T':
            ret = sscanf(&cmd[2],"%d",&x);
            if (1 != ret) { fail(); }
            ufo.throttle(x);
            break;
			
			// Command "E <int>" sets the elevator     
        case 'e':
        case 'E':
            ret = sscanf(&cmd[2],"%d",&x);
            if (1 != ret) { fail(); }
            ufo.elevator(x);
            break;
			
			// Command "A <int>" sets the aileron 
        case 'a':
        case 'A':
            ret = sscanf(&cmd[2],"%d",&x);
            if (1 != ret) { fail(); }
            ufo.aileron(x);
            break;
			
			// Command "R <int>" sets the rudder
        case 'r':
        case 'R':
            ret = sscanf(&cmd[2],"%d",&x);
            if (1 != ret) { fail(); }
            ufo.rudder(x);
            break;
			
			// Command "S" or "H" returns to hover     
        case 'h':
        case 'H':
        case 's':
        case 'S':
            ufo.stop();
            break;
			
			// Command "G <int>" sets the gain
        case 'g':
        case 'G':
            ret = sscanf(&cmd[2],"%d",&x);
            if (1 != ret) { fail(); }
            ufo.adjustGain(x);
            break;
            
			// Command "X" stops the thing
        case 'x':
        case 'X':
        default:
            fail();
            break;
    }
}