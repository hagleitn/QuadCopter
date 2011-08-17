#include <HardwareSerial.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <WProgram.h>

using namespace std;

void HardwareSerial::begin(int baud) {
	const int fd = fileno(stdin);
	const int fcflags = fcntl(fd,F_GETFL);
	if (fcflags<0) { 
		cout << "ERROR " << fcflags << endl; 
	}
	if (fcntl(fd,F_SETFL,fcflags | O_NONBLOCK) <0) { 
		cout << "ERROR fcntl" << endl;
	}
}

bool HardwareSerial::available() {
	int c = getc(stdin);
	if (c == EOF) {
		return false;
	} else {
		if (c == 91) {
			rcDown();
			return false;
		} else if (c == 93) {
			rcUp();
			return false;
		} else if (c == 10) {
			return false;
		} else if (((char)c)=='-') { 
            startSim(100);
            return false;
        }
        else {
			ungetc(c,stdin);
			return true;
		}
	}
}

char HardwareSerial::read() {
	return getc(stdin);
}

void HardwareSerial::println(byte b, int flag) {
	cout << hex << "0x" << (int)b << dec << endl;
}

void HardwareSerial::print(double f) {
	cout << f;
}

void HardwareSerial::println(double f) {
	cout << f << endl;
}

void HardwareSerial::print(string s) {
	cout << s;
}

void HardwareSerial::println(string s) {
	cout << s << endl;
}

HardwareSerial Serial;
