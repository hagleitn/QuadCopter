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
#include <Signal.h>
#include <SignalListener.h>
#include <UltraSoundSignal.h>
#include <AccelerometerSignal.h>
#include <RemoteControl.h>
#include <AutoControl.h>

int aileronOut =        12; //White 
int rudderOut =         13; //Yellow 
int throttleOut =       10;  //Orange 
int elevatorOut =       11; //Red 
int gainOut =           9;  //Green (Gain/Gear)

int aileronIn =         4; //White 
int rudderIn =          2; //Yellow 
int throttleIn =        5; //Orange 
int elevatorIn =        3; //Red 
int gainIn =            9;  //Green (Gain/Gear)

int killPin =           9; // LOW kills the flight
int pingPin =           8; // ultrasound sensor

int longitudinalPin =   6;
int lateralPin =        7;
long time = 0;

char controlMask = ~(0x01 << 2); // control all inputs but throttle

QuadCopter ufo(aileronOut, rudderOut, throttleOut, elevatorOut, gainOut); // the flying machine
RemoteControl rc(ufo,aileronIn, rudderIn, throttleIn, elevatorIn, gainIn); // receives rc input for manual override
UltraSoundSignal distance(pingPin, 2); // height information
AccelerometerSignal longitudinalAcceleration(longitudinalPin,2);
AccelerometerSignal lateralAcceleration(lateralPin,2);
FlightComputer computer(ufo,rc,distance,longitudinalAcceleration,lateralAcceleration); // the auto pilot

HardwareReader reader(Serial); // reading commands (take off, land...) from Serial port
FlightComputerCommandParser parser(computer); // the commands
SerialController controller(parser, killPin, reader); // drives the command processing

void setup() {
    Serial.begin(9600);
    ufo.init();
    rc.init();
    rc.setControlMask(controlMask);
    distance.init();
    longitudinalAcceleration.init();
    lateralAcceleration.init();
    computer.init();
    controller.init();
}

void loop() {
    controller.executeCommand();
    computer.adjust();
}
