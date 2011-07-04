#include <Memory.h>
#include <AutoControl.h>
#include <ControlListener.h>
#include <SignalListener.h>

class DummyListener : public ControlListener {
public:
    virtual void adjust(double value) {
        Serial.println("Set to: ");
        Serial.println(value);
    }
};

DummyListener listener;

AutoControl control(listener, 10, 0.5, 0.001, 0, 100, 10);

int i;

void setup() {
    Serial.begin(9600);
    control.init();
    i = 0;
}

void loop() {
    control.update(i);
    i = (i+1)%11;
    delay(1000);
}
