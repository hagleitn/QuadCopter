#include "Servo.h"
#include "SerialController.h"
#include "QuadCopter.h"
#include "Tokenizer.h"

int aileronPin = 12; //White 
int rudderPin = 9; //Yellow 
int throttlePin = 10;  //Orange 
int elevatorPin = 11; //Red 
int gainPin = 7;  //Green (Gain/Gear)
int killPin = 8; // LOW kills the flight

SerialController controller(
    QuadCopter(aileronPin, rudderPin, throttlePin, elevatorPin, gainPin),
    Tokenizer(';',0),
    killPin
);

void setup() {
    Serial.begin(9600);
    controller.init();
}

void loop() {
    controller.executeCommand();
}
