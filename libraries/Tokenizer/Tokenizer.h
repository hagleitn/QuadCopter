#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "WProgram.h"

class Tokenizer {

public:
    
    Tokenizer(char delim, size_t size = 127) : 
        delim(delim), buf(0), p(0), startToken(true), size(size) {}
    ~Tokenizer() { if(0 != buf) free(buf); }
    void init();
    const char *read();

private:
    
    char delim;
    char *buf;
    char *p;
    bool startToken;
    size_t size;
};

#endif