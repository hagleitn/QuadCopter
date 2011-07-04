#include <Memory.h>
#include <MedianMeasurement.h>
#include <SignalListener.h>
#include <UltraSoundSignal.h>

class DummyListener : public SignalListener {
public:
    virtual void update(double x) {
        Serial.print("Location: ");
        Serial.println(x);
    }
};

int pingPin = 2; // ultrasound sensor

UltraSoundSignal distance(pingPin);
DummyListener listener;

void setup() {
    Serial.begin(9600);
    distance.init();
    distance.registerListener(&listener);
}

void loop() {
    distance.signal();
    delay(500);
}
