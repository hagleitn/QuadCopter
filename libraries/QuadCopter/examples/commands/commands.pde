#include "Servo.h"
#include "QuadCopter.h"

char cmd[256];
char *p;

int aileronPin = 12; //White 
int rudderPin = 9; //Yellow 
int throttlePin = 10;  //Orange 
int elevatorPin = 11; //Red 
int gainPin = 8;  //Green (Gain/Gear)

long start_sleep;
bool start_command;
long sleep_time;


QuadCopter ufo(aileronPin, rudderPin, throttlePin, elevatorPin, gainPin);

void setup() {
  Serial.begin(9600);

  ufo.init();

  cmd[255] = 0;
  p = cmd;
  sleep_time = 0;
  start_sleep = 0;
  start_command = false;
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
      if (x > -20) {x = -20;}
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
      sscanf(&cmd[2],"%d",&x);
      ufo.adjustGain(x);
      break;

    // Command "Z <int>" sleeps zzzz
    case 'z':
    case 'Z':
      sscanf(&cmd[2],"%d",&x);
	  sleep_time = x;
	  start_sleep = millis();
      break;

	// Command "X" stops the thing
    case 'x':
    case 'X':
      default:
      ufo.stop();
      ufo.throttle(QuadCopter::MIN_SPEED);
      break;
  }
}

void loop() {
  
  if (start_sleep != 0) {
    if (millis()-start_sleep < sleep_time) {
      delay(100);
      return;
    } else {
      sleep_time = 0;
      start_sleep = 0;
    }
  }

  if (Serial.available() > 0) {
    *p = Serial.read();

	if (start_command && *p == ' ') {
	  return;
	} else {
	  start_command = false;
	}
    
    if (*p == ';' || p-cmd == 254) {
      *p = 0;
      Serial.print(cmd);
      Serial.print("; ");
      doCmd();
      p = cmd;
	  start_command = true;
    } else {
      ++p;
    }
  } 
}
