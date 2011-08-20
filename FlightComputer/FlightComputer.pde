#include <Memory.h>
#include <Servo.h>
#include <SerialController.h>
#include <QuadCopter.h>
#include <Tokenizer.h>
#include <Reader.h> 
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

const int aileronOut =        5; //White 
const int rudderOut =         2; //Yellow 
const int throttleOut =       4; //Orange 
const int elevatorOut =       3; //Red 
const int gainOut =          14;  //Green (Gain/Gear)

const int aileronIn =         9; //White 
const int rudderIn =          6; //Yellow 
const int throttleIn =        8; //Orange 
const int elevatorIn =        7; //Red 
const int gainIn =           14; //Green (Gain/Gear)

const int pingPin =          10; // ultrasound sensor

const int longitudinalPin =  12; // tilt sensor long axis
const int lateralPin =       13; // tilt sensor lat axis

const int listenerSize =      2; // maximum listeners for signal updates

const int baud =              9600; // baud rate for serial communication

const char controlMask = ~RemoteControl::THROTTLE_MASK; // control all inputs but throttle

QuadCopter ufo(aileronOut, rudderOut, throttleOut, elevatorOut, gainOut); // the flying machine
RemoteControl rc(ufo,aileronIn, rudderIn, throttleIn, elevatorIn, gainIn); // receives rc input for manual override
UltraSoundSignal distance(pingPin, listenerSize); // height information
AccelerometerSignal longitudinalAcceleration(longitudinalPin, listenerSize);
AccelerometerSignal lateralAcceleration(lateralPin, listenerSize);
FlightComputer computer(ufo, rc, distance, longitudinalAcceleration, lateralAcceleration); // the auto pilot

HardwareReader reader(Serial); // reading commands (take off, land...) from Serial port
FlightComputerCommandParser parser(computer); // the commands
SerialController controller(parser, reader); // drives the command processing

void setup() {
    Serial.begin(baud);
    ufo.init();
    rc.init();
    rc.setControlMask(controlMask);
    distance.init();
    distance.useMedian(false);
    longitudinalAcceleration.init();
    lateralAcceleration.init();
    computer.init();
    controller.init();
}

void loop() {
    controller.executeCommand();
    computer.adjust();
}
