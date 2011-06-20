#ifndef QUADCOPTER_H
#define QUADCOPTER_H

#include "WProgram.h"
#include "Servo.h"

class QuadCopter {
public:
	
	typedef enum {LONGITUDINAL=0, LATERAL, VERTICAL, ROTATIONAL} Direction;
	
	QuadCopter(int,int,int,int,int);
	~QuadCopter() {}
	void init();
	void move(int,int,int,int);
	void move(int[]);
	void move(Direction,int);
	void stop(Direction);
	void stop();
	void throttle(int speed) {move(VERTICAL,speed);}
	void elevator(int speed) {move(LONGITUDINAL,speed);}
	void aileron(int speed) {move(LATERAL,speed);}
	void rudder(int speed) {move(ROTATIONAL,speed);}
	void adjustGain(int);
	
	static const int DEGREES_OF_FREEDOM = 4;
	static const int MIN_SPEED = -100;
	static const int STOP_SPEED = 0;
	static const int MAX_SPEED = 100;

private:
	
	void arm();
	void attach();
	
	Servo servos[DEGREES_OF_FREEDOM];
	Servo gain;
	
	int speed[DEGREES_OF_FREEDOM];
	
	int pins[DEGREES_OF_FREEDOM];
	int gainPin;
};

#endif