#include <Memory.h>
#include <Servo.h>
#include <QuadCopter.h>
#include <RemoteControl.h>

int aileronPinOUT = 12; //White 
int rudderPinOUT = 9; //Yellow 
int throttlePinOUT = 10;  //Orange 
int elevatorPinOUT = 11; //Red 
int gainPinOUT = 8;  //Green (Gain/Gear)

int aileronPinIN = 1;
int rudderPinIN = 2;
int throttlePinIN = 3;
int elevatorPinIN = 4;
int gainPinIN = 5;


QuadCopter ufo(aileronPinOUT, rudderPinOUT, throttlePinOUT, elevatorPinOUT, gainPinOUT);
RemoteControl rc(ufo, aileronPinIN, rudderPinIN, throttlePinIN, elevatorPinIN, gainPinIN);

void setup() {
    ufo.init();
    rc.init();
}

void loop() {
    rc.update();
}
