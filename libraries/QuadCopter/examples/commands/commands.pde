#include "Servo.h"
#include "QuadCopter.h"

char cmd[256];
char *p;
int aileronPin = 12; //White 
int rudderPin = 9; //Yellow 
int throttlePin = 10;  //Orange 
int elevatorPin = 11; //Red 
int gainPin = 8;  //Green (Gain/Gear) 
int potPin = 1; 

QuadCopter ufo(aileronPin, rudderPin, throttlePin, elevatorPin, gainPin);

void setup() {
  Serial.begin(9600);
  cmd[255] = 0;
  p = cmd;
  ufo.init();
}

void doCmd() {
  int x,y,z,r;
  switch(cmd[0]) {
    case 'm':
    case 'M':
      sscanf(&cmd[2],"%d, %d, %d, %d", &x,&y,&z,&r);
      ufo.move(x,y,z,r);
      break;
    
    case 't':
    case 'T':
      sscanf(&cmd[2],"%d",&x);
      ufo.throttle(x);
      break;
      
    case 'e':
    case 'E':
      sscanf(&cmd[2],"%d",&x);
      ufo.elevator(x);
      break;

    case 'a':
    case 'A':
      sscanf(&cmd[2],"%d",&x);
      ufo.aileron(x);
      break;

    case 'r':
    case 'R':
      sscanf(&cmd[2],"%d",&x);
      ufo.rudder(x);
      break;

    case 'g':
    case 'G':
      scanf(&cmd[2],"%d",&x);
      ufo.adjustGain(x);
      break;

    default:
      // nothing
      break;
  }
}

void loop() {
  if (Serial.available() > 0) {
    *p = Serial.read();
    
    if (*p == '\n' || p-cmd == 254) {
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
