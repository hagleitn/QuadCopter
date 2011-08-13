#include <Tokenizer.h>

void Tokenizer::init() {
    p = buf = (char*) malloc(size+1);
    buf[size] = 0;
}

const char *Tokenizer::read() {
    char *ret = 0;
    char c;
    
    while (reader.available() > 0) {
        c = reader.read();

        if (startToken && (c == ' ' || c == '\n' || c == '\t' || c == '\r')) {
            continue;
        } else {
            startToken = false;
        }

        if (c == delim || p-buf == size) {
            *p = 0;
            p = ret = buf;
            startToken = true;
            Serial.println(ret);
            break;
        } else {
            *p++ = c;
        }
    }
    
    return ret;
}