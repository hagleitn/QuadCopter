#include <Memory.h>
#include <MedianMeasurement.h>
#include <Signal.h>
#include <SignalListener.h>

class DummyListener : public SignalListener {
public:
    virtual void update(double x, long time) {
        Serial.print("Duration: ");
        Serial.print(x);
        Serial.print(", at: ");
        Serial.println(time);
    }
};

int pin = 2; // some pulse in sensor

Signal s(pin,1);
DummyListener listener;

void setup() {
    Serial.begin(9600);
    s.init();
    s.registerListener(&listener);
}

void loop() {
    s.signal();
    delay(500);
}
