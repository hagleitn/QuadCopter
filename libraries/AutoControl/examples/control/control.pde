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

AutoControl::Configuration conf = {10,0.5,0.001,0,100};
AutoControl control(listener);

int i;

void setup() {
    Serial.begin(9600);
    control.init();
    control.setConfiguration(conf);
    control.setGoal(10);
    i = 0;
}

void loop() {
    control.update(i,millis());
    i = (i+1)%11;
    delay(1000);
}
