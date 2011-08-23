#include <Signal.h>

void Signal::init() {
    median.init();
    listener = (SignalListener**) malloc(sizeof(SignalListener*)*listenerSize);
    for (int i = 0; i < listenerSize; ++i) {
        listener[i] = 0;
    }
}

long Signal::measure() {
    pinMode(pin, INPUT);
    return pulseIn(pin, HIGH);
}

bool Signal::read() {
    long duration;
    
    setupMeasurement();

    duration = measure();
    
    double newMeasurement;
    
    bool success = convert(duration,newMeasurement);
    
    if (success) {
        if (smooth) {
            median.pushMeasurement(newMeasurement);
            success = median.getMedian(measurements[index],time[index]);
        } else {
            measurements[index] = newMeasurement;
            time[index] = millis();
        }
        
        if (success) {
            ++index;
            if (index >= size) {
                full = true;
                index %= size;
            }
        }
    }
    return success;
}

void Signal::registerListener(SignalListener *listener) {
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

void Signal::signal() {
    if (read()) {
        int newest = (size+index-1)%size;
        for (int i = 0; i < listenerSize; ++i) {
            if (listener[i] != 0) {
                listener[i]->update(measurements[newest],time[newest]);
            }
        }
    }
}
