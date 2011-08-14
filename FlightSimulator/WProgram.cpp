#include <WProgram.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

static struct timeval start;

const int aileronOut =        12; //White 
const int rudderOut =         13; //Yellow 
const int throttleOut =       10; //Orange 
const int elevatorOut =       11; //Red 
const int gainOut =           9;  //Green (Gain/Gear)

const int aileronIn =         4; //White 
const int rudderIn =          2; //Yellow 
const int throttleIn =        5; //Orange 
const int elevatorIn =        3; //Red 
const int gainIn =            9; //Green (Gain/Gear)

const int pingPin =           8; // ultrasound sensor

const int longitudinalPin =   6; // tilt sensor long axis
const int lateralPin =        7; // tilt sensor lat axis

const int listenerSize =      2; // maximum listeners for signal updates

int height = 10;
long lastMillis = 0;
int lastThrottle = 0;
const double multiplier = 200/50;
ofstream myfile;

void init() {
	gettimeofday(&start, NULL);
	myfile.open ("data.txt");
}

void updateHeight() {
	if (lastThrottle > -27) {
		int time = millis();
		height += ((time - lastMillis)/1000.0)*(multiplier*lastThrottle);
		if (height < 10) {
			height = 10;
		}
		myfile << time << "\t" << height << endl;
		lastMillis = time;
	}
}

void throttle(int val) {
	updateHeight();
	lastThrottle = val;
}

long millis() {
   struct timeval end;

    long mtime, seconds, useconds;    

    gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
	return mtime;
}

int map(double val, double srcMin, double srcMax, double dstMin, double dstMax) {
	return (int)(dstMin + ((val-srcMin)/(srcMax-srcMin))*(dstMax-dstMin));
}

int pulseIn(int pin, int mode, int time) {
    int value = 0;

	if (pin == pingPin) {
		updateHeight();
		value = height * 29 * 2;
	}
	
	return value;
}

void pinMode(int pin, int mode) {
	return;
}

void delayMicroseconds(long val) {
	usleep(val);
}

void digitalWrite(int pin, int value) {
	return;
}
