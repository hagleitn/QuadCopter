#include <PressureSignal.h>
#include <SPI.h>
#include <limits.h>

void PressureSignal::init() {
    Signal::init();
    
    // start the SPI library:
    SPI.begin();
    
    // initalize the  data ready and chip select pins:
    pinMode(dataReadyPin, INPUT);
    pinMode(chipSelectPin, OUTPUT);
    
    //Configure SCP1000 for low noise configuration:
    writeRegister(0x02, 0x2D);
    writeRegister(0x01, 0x03);
    writeRegister(0x03, 0x02);
}    

long PressureSignal::measure() {
    writeRegister(0x03, 0x0A);
    
    // don't do anything until the data ready pin is high:
    if (digitalRead(dataReadyPin) == HIGH) {
        //Read the pressure data highest 3 bits:
        byte  pressure_data_high = readRegister(PRESSURE, 1);
        pressure_data_high &= 0b00000111; //you only needs bits 2 to 0
        
        //Read the pressure data lower 16 bits:
        unsigned int pressure_data_low = readRegister(PRESSURE_LSB, 2);
        //combine the two parts into one 19-bit number:
        return (pressure_data_high << 16) | pressure_data_low;
    } else {
        return LONG_MIN;
    }
}

bool PressureSignal::convert(long measurement, double& value) {
    value = measurement/4.0;
    return measurement != LONG_MIN;
}

unsigned int PressureSignal::readRegister(byte thisRegister, int bytesToRead ) {
    byte inByte = 0;           // incoming byte from the SPI
    unsigned int result = 0;   // result to return
    // SCP1000 expects the register name in the upper 6 bits
    // of the byte. So shift the bits left by two bits:
    thisRegister = thisRegister << 2;
    // now combine the address and the command into one byte
    byte dataToSend = thisRegister & READ;
    // take the chip select low to select the device:
    digitalWrite(chipSelectPin, LOW);
    // send the device the register you want to read:
    SPI.transfer(dataToSend);
    // send a value of 0 to read the first byte returned:
    result = SPI.transfer(0x00);
    // decrement the number of bytes left to read:
    bytesToRead--;
    // if you still have another byte to read:
    if (bytesToRead > 0) {
        // shift the first byte left, then get the second byte:
        result = result << 8;
        inByte = SPI.transfer(0x00);
        // combine the byte you just got with the previous one:
        result = result | inByte;
        // decrement the number of bytes left to read:
        bytesToRead--;
    }
    // take the chip select high to de-select:
    digitalWrite(chipSelectPin, HIGH);
    // return the result:
    return(result);
}


void PressureSignal::writeRegister(byte thisRegister, byte thisValue) {
    
    // SCP1000 expects the register address in the upper 6 bits
    // of the byte. So shift the bits left by two bits:
    thisRegister = thisRegister << 2;
    // now combine the register address and the command into one byte:
    byte dataToSend = thisRegister | WRITE;
    
    // take the chip select low to select the device:
    digitalWrite(chipSelectPin, LOW);
    
    SPI.transfer(dataToSend); //Send register location
    SPI.transfer(thisValue);  //Send value to record into register
    
    // take the chip select high to de-select:
    digitalWrite(chipSelectPin, HIGH);
}
