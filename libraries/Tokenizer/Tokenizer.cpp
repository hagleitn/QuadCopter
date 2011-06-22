#include <Tokenizer.h>
#include <ctype.h>
#include <HardwareSerial.h>


void Tokenizer::init() {
    Serial.println("Tokenizer::init()");
    p = buf = (char*) malloc(size+1);
    buf[size] = 0;
}

const char *Tokenizer::read() {
    char *ret = 0;
    while (Serial.available() > 0) {
        *p = Serial.read();

        if (startToken && isspace(*p)) {
            Serial.println("removing whitespace");
            continue;
        } else {
            startToken = false;
        }

        if (*p == delim || p-buf == size) {
            *p = 0;
            p = ret = buf;
            startToken = true;
            Serial.println(ret);
            break;
        } else {
            ++p;
        }
    }
    return ret;
}