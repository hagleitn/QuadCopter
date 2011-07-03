#ifndef DISTANCE_LISTENER_H
#define DISTANCE_LISTENER_H

#include "WProgram.h"

class DistanceListener {
public:
    virtual void update(long x, long v, long time) = 0;
};

#endif
