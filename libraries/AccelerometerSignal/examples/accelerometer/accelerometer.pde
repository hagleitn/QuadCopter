#include <Memory.h>
#include <MedianMeasurement.h>
#include <SignalListener.h>
#include <AccelerometerSignal.h>

class DummyListener : public SignalListener {
public:
    virtual void update(double x, long time) {
        Serial.print("Force: ");
        Serial.print(x);
        Serial.print(", at: ");
        Serial.println(time);
    }
};

int pin = 5; // accelerometer sensor

AccelerometerSignal force(pin,1);
DummyListener listener;

void setup() {
    Serial.begin(9600);
    force.init();
    force.registerListener(&listener);
}

void loop() {
    force.signal();
    delay(500);
}
