#ifndef SERVO_H
#define SERVO_H

class Servo {
public:
    void attach(int);
	void attach(int,int,int);
	void write(int value);
	void writeMicroseconds(int value);
	int read();
	int readMicroseconds();
private:
	int pin;
	int value;
};
#endif
