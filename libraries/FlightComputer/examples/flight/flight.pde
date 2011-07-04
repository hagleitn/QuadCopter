#include <Memory.h>
#include <Servo.h>
#include <SerialController.h>
#include <QuadCopter.h>
#include <Tokenizer.h>
#include <HardwareReader.h>
#include <CommandParser.h>
#include <FlightComputer.h>
#include <FlightComputerCommandParser.h>
#include <MedianMeasurement.h>
#include <SignalListener.h>
#include <UltraSoundSignal.h>
#include <RemoteControl.h>
#include <AutoControl.h>

int aileronOut = 12; //White 
int rudderOut = 9; //Yellow 
int throttleOut = 10;  //Orange 
int elevatorOut = 11; //Red 
int gainOut = 8;  //Green (Gain/Gear)

int aileronIn = 1; //White 
int rudderIn = 4; //Yellow 
int throttleIn = 5;  //Orange 
int elevatorIn = 6; //Red 
int gainIn = 7;  //Green (Gain/Gear)

int killPin = 3; // LOW kills the flight
int pingPin = 2; // ultrasound sensor

HardwareReader reader(Serial);
QuadCopter ufo(aileronOut, rudderOut, throttleOut, elevatorOut, gainOut);
UltraSoundSignal distance(pingPin);
RemoteControl rc(ufo,aileronIn, rudderIn, throttleIn, elevatorIn, gainIn);
FlightComputer computer(ufo,rc);
FlightComputerCommandParser parser(computer);
SerialController controller(parser, killPin, reader);

int minTime = 100;
long lastTime = 0;
long time = 0;

void setup() {
    Serial.begin(9600);
    ufo.init();
    rc.init();
    computer.init();
    controller.init();
    distance.init();
    distance.registerListener(&computer);
}

void loop() {
    time = millis();
    controller.executeCommand();
    if (time - lastTime > minTime) {
        distance.signal();
        lastTime = time;
    }
    computer.adjust();
}
