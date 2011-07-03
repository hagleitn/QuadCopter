#include <Memory.h>
#include <MedianMeasurement.h>
#include <DistanceListener.h>
#include <UltraSoundSignal.h>

class DummyListener : public DistanceListener {
public:
    virtual void update(long x, long v, long time) {
        Serial.print("Location: ");
        Serial.print(x);
        Serial.print(" Speed: ");
        Serial.print(v);
        Serial.print(" Time: ");
        Serial.println(time);
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
