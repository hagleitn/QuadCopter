#ifndef HARD_WARE_SERIAL_H
#define HARD_WARE_SERIAL_H
#include <string>
using std::string;

typedef unsigned char byte;

class HardwareSerial {
public:
	void begin(int);
	bool available();
	char read();
	void println(byte b, int flag);
	void print(double f);
	void println(double f);
	void print(string);
	void println(string);
	void println() { println(""); }
};


extern HardwareSerial Serial;
#endif
