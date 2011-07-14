#include <Tokenizer.h>
#include <ctype.h>


void Tokenizer::init() {
    p = buf = (char*) malloc(size+1);
    buf[size] = 0;
}

const char *Tokenizer::read() {
    char *ret = 0;
    while (reader.available() > 0) {
        *p = reader.read();

        if (startToken && isspace(*p)) {
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