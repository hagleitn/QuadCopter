#include <Tokenizer.h>
#include <ctype.h>


void Tokenizer::init() {
    p = buf = (char*) malloc(size);
    if (baud != 0) {
        Serial.begin(baud);
    }
}

const char *Tokenizer::read() {
    char *ret = 0;
    while (Serial.available() > 0) {
        *p = Serial.read();

        if (startToken && isspace(*p)) {
            continue;
        } else {
            startToken = false;
        }

        if (*p == delim || p-buf == size) {
            *p = 0;
            p = buf;
            startToken = true;
            ret = buf;
            break;
        } else {
            ++p;
        }
    }
	Serial.print("Tokenizer::read - \"");
	Serial.print(ret);
	Serial.println("\"");
    return ret;
}