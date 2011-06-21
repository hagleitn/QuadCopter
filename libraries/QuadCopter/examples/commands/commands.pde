#include "Servo.h"
#include "QuadCopter.h"

char cmd[256];
char *p;

int aileronPin = 12; //White 
int rudderPin = 9; //Yellow 
int throttlePin = 10;  //Orange 
int elevatorPin = 11; //Red 
int gainPin = 8;  //Green (Gain/Gear)

QuadCopter ufo(aileronPin, rudderPin, throttlePin, elevatorPin, gainPin);

void setup() {
  Serial.begin(9600);

  ufo.init();

  cmd[255] = 0;
  p = cmd;
}

void doCmd() {
  int x,y,z,r;
  switch(cmd[0]) {
    // Command "M <int>, <int>, <int>, <int>" will set all 4 speeds at once
    case 'm':
    case 'M':
      sscanf(&cmd[2],"%d, %d, %d, %d", &x,&y,&z,&r);
      ufo.move(x,y,z,r);
      break;

    // Command "T <int>" sets the throttle
    case 't':
    case 'T':
      sscanf(&cmd[2],"%d",&x);
      ufo.throttle(x);
      break;

    // Command "E <int>" sets the elevator     
    case 'e':
    case 'E':
      sscanf(&cmd[2],"%d",&x);
      ufo.elevator(x);
      break;

    // Command "A <int>" sets the aileron 
    case 'a':
    case 'A':
      sscanf(&cmd[2],"%d",&x);
      ufo.aileron(x);
      break;

    // Command "R <int>" sets the rudder
    case 'r':
    case 'R':
      sscanf(&cmd[2],"%d",&x);
      ufo.rudder(x);
      break;

    // Command "S" returns to hover     
    case 's':
    case 'S':
      ufo.stop();
      break;

    // Command "X" stops the thing
    case 'x':
    case 'X':
      ufo.stop();
      ufo.throttle(QuadCopter::MIN_SPEED);
      break;

    // Command "G <int>" sets the gain
    case 'g':
    case 'G':
      sscanf(&cmd[2],"%d",&x);
      ufo.adjustGain(x);
      break;

    // Command "Z <int>" sleeps zzzz
    case 'z':
    case 'Z':
      sscanf(&cmd[2],"%d",&x);
      delay(x);
      break;

    default:
      // nothing
      break;
  }
}

void loop() {
  if (Serial.available() > 0) {
    *p = Serial.read();
    
    if (*p == ';' || p-cmd == 254) {
      *p = 0;
      Serial.print("I received: ");
      Serial.println(cmd);
      doCmd();
      p = cmd;
    } else {
      ++p;
    }
  } 
}
