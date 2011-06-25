#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

void *operator new(size_t size);
void operator delete(void *m);

#endif
