#include <Memory.h>
#include <MedianMeasurement.h>
#include <Signal.h>
#include <SignalListener.h>
#include <SPI.h>
#include <PressureSignal.h>

class DummyListener : public SignalListener {
public:
    virtual void update(double x, long time) {
        Serial.print("Pressure: ");
        Serial.print(x);
        Serial.print(", at: ");
        Serial.println(time);
    }
};

int dataPin = 6;
int chipPin = 7;

PressureSignal pressure(dataPin,chipPin,1);
DummyListener listener;

void setup() {
    Serial.begin(9600);
    pressure.init();
    pressure.registerListener(&listener);
}

void loop() {
    pressure.signal();
    delay(500);
}
