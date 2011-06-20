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
  Serial.begin(9600);
  ufo.init();
} 

void loop() {
  int foo = analogRead(potPin);
  ufo.throttle(map(foo,0,1023,-100,100));
  Serial.print(map(foo,0,1023,-100,100)); 
  Serial.print("\n"); 
  delay(10);
} 

