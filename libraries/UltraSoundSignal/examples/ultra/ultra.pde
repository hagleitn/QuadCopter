#include <Memory.h>
#include <MedianMeasurement.h>
#include <Signal.h>
#include <SignalListener.h>
#include <UltraSoundSignal.h>

class DummyListener : public SignalListener {
public:
    virtual void update(double x, long time) {
        Serial.print("Location: ");
        Serial.print(x);
        Serial.print(", at: ");
        Serial.println(time);
    }
};

int pingPin = 2; // ultrasound sensor

UltraSoundSignal distance(pingPin,1);
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
