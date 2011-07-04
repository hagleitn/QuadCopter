#ifndef CONTROL_LISTENER_H
#define CONTROL_LISTENER_H

#include "WProgram.h"

class ControlListener {
public:
    virtual void adjust(double x) = 0;
};

#endif
