#include <Memory.h>
#include <Servo.h>
#include <QuadCopter.h>
#include <RemoteControl.h>

int aileronPinOUT = 12; //White 
int rudderPinOUT = 9; //Yellow 
int throttlePinOUT = 10;  //Orange 
int elevatorPinOUT = 11; //Red 
int gainPinOUT = 8;  //Green (Gain/Gear)

int aileronPinIN = 2;
int rudderPinIN = 3;
int throttlePinIN = 4;
int elevatorPinIN = 5;
int gainPinIN = 14;


QuadCopter ufo(aileronPinOUT, rudderPinOUT, throttlePinOUT, elevatorPinOUT, gainPinOUT);
RemoteControl rc(ufo, aileronPinIN, rudderPinIN, throttlePinIN, elevatorPinIN, gainPinIN);

void setup() {
    Serial.begin(9600);
    ufo.init();
    rc.init();
}

void loop() {
    delay(1000);
    rc.update();
}
