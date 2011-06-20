#include "Servo.h"
#include "QuadCopter.h"

int aileronPin = 12; //White 
int rudderPin = 9; //Yellow 
int throttlePin = 10;  //Orange 
int elevatorPin = 11; //Red 
int gainPin = 8;  //Green (Gain/Gear) 
int potPin = 1; 

QuadCopter ufo(aileronPin, rudderPin, throttlePin, elevatorPin, gainPin);

void setup() { 
  ufo.init();
  delay(1000);
  ufo.move(QuadCopter::VERTICAL,10);
  delay(3000);
  ufo.stop();
} 

void loop() { 
  ufo.stop();
  delay(1000);
  ufo.move(QuadCopter::LONGITUDINAL,10);
  delay(5000);
  ufo.stop();
  delay(1000);
  ufo.move(QuadCopter::LATERAL,10);
  delay(5000);
  ufo.stop();
  delay(1000);
  ufo.move(QuadCopter::LONGITUDINAL,-10);
  delay(5000);
  ufo.stop();
  delay(1000);
  ufo.move(QuadCopter::LATERAL,-10);
  delay(5000);
} 

