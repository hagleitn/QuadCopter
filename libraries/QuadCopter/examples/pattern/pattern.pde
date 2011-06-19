#include "Servo.h"
#include "QuadCopter.h"

int aileronPin = 12; 
int rudderPin = 9; 
int throttlePin = 10; 
int elevatorPin = 11; 
int gainPin = 8; 
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

