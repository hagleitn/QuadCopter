#include <AccelerometerSignal.h>

void AccelerometerSignal::init() {
    median.init();
    listener = (SignalListener**) malloc(sizeof(SignalListener*)*listenerSize);
    for (int i = 0; i < listenerSize; ++i) {
        listener[i] = 0;
    }
};

bool AccelerometerSignal::read() {
    long duration;
    
    pinMode(pin, INPUT);
    duration = pulseIn(pin, HIGH);
    
    // convert the time into a force
    double force = millig(duration);
    
    median.pushMeasurement(force);
    bool success = median.getMedian(this->force[index],time[index]);
    if (success) {
        ++index;
        if (index >= size) {
            full = true;
            index %= size;
        }
    }
    return success;
}

double AccelerometerSignal::millig(long microseconds)
{
    return ((microseconds / 10) - 500) * 8;
}

void AccelerometerSignal::registerListener(SignalListener *listener) {
    int index = -1;
    for (int i = 0; i < listenerSize; ++i) {
        if (this->listener[i] == 0) {
            index = i;
            break;
        }
    }
    if (index >= 0) {
        this->listener[index] = listener;
    }
}

void AccelerometerSignal::signal() {
    if (read()) {
        int newest = (size+index-1)%size;
        for (int i = 0; i < listenerSize; ++i) {
            if (listener[i] != 0) {
                listener[i]->update(force[newest],time[newest]);
            }
        }
    }
}
