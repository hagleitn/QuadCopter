#include <Memory.h>
#include <Servo.h>
#include <SerialController.h>
#include <QuadCopter.h>
#include <QuadCopterCommandParser.h>
#include <CommandParser.h>
#include <Tokenizer.h>
#include <HardwareReader.h>
#include <QuadCopterCommandParser.h>

int aileronPin = 12; //White 
int rudderPin = 9; //Yellow 
int throttlePin = 10;  //Orange 
int elevatorPin = 11; //Red 
int gainPin = 7;  //Green (Gain/Gear)

HardwareReader reader(Serial);
QuadCopter ufo(aileronPin, rudderPin, throttlePin, elevatorPin, gainPin);
QuadCopterCommandParser parser(ufo);
SerialController controller(parser, reader);

void setup() {
    Serial.begin(9600);
    ufo.init();
    controller.init();
}

void loop() {
    controller.executeCommand();
}
