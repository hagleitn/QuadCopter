#include <Memory.h>

void *operator new(size_t size) { return malloc(size); }
void operator delete(void *m) { if (0 != m) free(m); }
