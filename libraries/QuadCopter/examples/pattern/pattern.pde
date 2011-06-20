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
  ufo.up();
  delay(3000);
  ufo.hover();
} 

void loop() { 
  ufo.hover();
  delay(1000);
  ufo.left();
  delay(5000);
  ufo.hover();
  delay(1000);
  ufo.forward();
  delay(5000);
  ufo.hover();
  delay(1000);
  ufo.right();
  delay(5000);
  ufo.hover();
  delay(1000);
  ufo.backward();
  delay(5000);
} 

