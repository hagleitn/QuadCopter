#ifndef QUADCOPTER_H
#define QUADCOPTER_H

#include "WProgram.h"
#include "Servo.h"

#define DEFAULT_SPEED 10

class QuadCopter {
public:
	
	typedef enum {LEFT,RIGHT} Direction;
	
	QuadCopter(	int aileronPin, 
				int rudderPin, 
				int throttlePin, 
				int evelatorPin, 
				int gainPin) :
				aileronPin(aileronPin),
				rudderPin(rudderPin),
				throttlePin(throttlePin),
				elevatorPin(elevatorPin),
				gainPin(gainPin)
				{ }
	~QuadCopter() {}
	void init();
	void up(int speed = DEFAULT_SPEED);
	void down(int speed = DEFAULT_SPEED);
	void left(int speed = DEFAULT_SPEED);
	void right(int speed = DEFAULT_SPEED);
	void forward(int speed = DEFAULT_SPEED);
	void backward(int speed = DEFAULT_SPEED);
	void adjustGain(int gain = DEFAULT_SPEED);
	void rotate(Direction, int speed = DEFAULT_SPEED);
	void hover();
	
	static const int STOP_SPEED = 0;
	static const int MAX_SPEED = 100;

private:
	
	void arm();
	void attach();
	void setSpeed(Servo &, int);
	
	Servo aileron;
	Servo rudder;
	Servo throttle;
	Servo elevator;
	Servo gain;
	
	int aileronPin;
	int rudderPin;
	int throttlePin;
	int elevatorPin;
	int gainPin;
};

#endif