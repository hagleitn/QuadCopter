#ifndef READER_H
#define READER_H

class Reader {
public:
	virtual int available() = 0;
	virtual char read() = 0;
};

#endif