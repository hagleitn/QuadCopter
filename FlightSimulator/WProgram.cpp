#include <WProgram.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

static struct timeval start;

const int aileronOut =        5; //White 
const int rudderOut =         2; //Yellow 
const int throttleOut =       4; //Orange 
const int elevatorOut =       3; //Red 
const int gainOut =          14;  //Green (Gain/Gear)

const int aileronIn =         9; //White 
const int rudderIn =          6; //Yellow 
const int throttleIn =        8; //Orange 
const int elevatorIn =        7; //Red 
const int gainIn =           14; //Green (Gain/Gear)

const int pingPin =          10; // ultrasound sensor

const int longitudinalPin =  12; // tilt sensor long axis
const int lateralPin =       13; // tilt sensor lat axis

const int listenerSize =      2; // maximum listeners for signal updates

static int height = 10;
static double speed = 0;
static double accel = 0;
static long lastMillis = 0;
static int lastThrottle = 0;
static const double multiplier = 1000/93.0;
static const double g = 1000;
static ofstream myfile;
static int rc = 1150;
static const int DELTA = 100;
static const int RC_MIN = 1150;
static const int RC_MAX = 1950;
static double error = 0;
static int duration = 0;
static bool started = false;
static const int goal = 150;


void init() {
	gettimeofday(&start, NULL);
    srand(time(NULL));
	myfile.open ("data.txt");
    startSim(100);
}

void startSim(int dur) {
    gettimeofday(&start, NULL);
    duration = dur;
    started = true;
}

void rcDown() {
	rc -= DELTA;
	if (rc < RC_MIN) {
		rc = RC_MIN;
	}
}

void rcUp() {
	rc += DELTA;
	if (rc > RC_MAX) {
		rc = RC_MAX;
	}
}

void updateHeight() {
    int time = millis();
    int oldHeight = height;
    double tDelta = (time - lastMillis)/1000.0;

    // f = thr*const-g
    accel = (multiplier*(lastThrottle+75)-g);
    if (height <= 10 && accel < 0) {
        accel = 0;
    }

    speed += tDelta*accel;

    height += tDelta*speed;
    if (height < 10) {
        height = 10;
        speed = 0;
    }

    double dHeight = goal - ((height+oldHeight)/2.0);
    if (dHeight < 0) dHeight *= -1;
    error += dHeight*tDelta;
    
    lastMillis = time;
    
    myfile << time << "\t" << height << "\t" << speed << "\t" << accel << "\t" << lastThrottle << endl;
}

void throttle(int val) {
	updateHeight();
	lastThrottle = val;
}

long millis() {
    if (!started) return 0;
    
    struct timeval end;
    
    long mtime, seconds, useconds;    
    
    gettimeofday(&end, NULL);
    
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    
    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
    //mtime *= 100;
    
    if (mtime == 0) mtime = 1;
    
    if (mtime > duration*1000) {
        cerr << (long)error << endl;
        exit(0);
    }
	return mtime;
}

int map(double val, double srcMin, double srcMax, double dstMin, double dstMax) {
	return (int)(dstMin + ((val-srcMin)/(srcMax-srcMin))*(dstMax-dstMin));
}

double rand_double() {
    double r = 0;
    while ((r = rand()) == 0);
    r = r/((double)RAND_MAX);
    return r;
}
    
double normal_distribution() {
    double r = sqrt(-2*log(rand_double()))*cos(2*M_PI*rand_double());
    return r;
}
    

int pulseIn(int pin, int mode, int time) {
    int value = 0;

	if (pin == pingPin) {
		updateHeight();
        double r = normal_distribution();
		value = height * 29 * 2 + r * 300;
	} else if (pin == throttleIn) {
		value = rc;
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
