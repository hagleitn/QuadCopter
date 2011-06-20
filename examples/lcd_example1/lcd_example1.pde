/*
  LiquidCrystal Library - scrollDisplayLeft() and scrollDisplayRight()
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD and uses the
 scrollDisplayLeft() and scrollDisplayRight() methods to scroll
 the text.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h>

// LiquidCrystal display with:
// rs on pin 10
// rw on pin 11
// enable on pin 12
// d4, d5, d6, d7 on pins 13, 14, 15, 16
//LiquidCrystal lcd(10, 11, 12, 13, 14, 15, 16);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);
int servoPin = 10;
Servo servo;
int analogValues[6] = {0,0,0,0,0,0};

byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};

void setup()
{
  pinMode(9,OUTPUT); //set the LED pin for digital output
  pinMode(8,INPUT); //set the tilt sensor pin for digital input
  
  //pinMode(servoPin,OUTPUT);
  servo.attach(servoPin,500,2500);
  
  lcd.createChar(0, smiley);
  lcd.clear();//clears the LCD and positions the cursor in the upper-left corner
  lcd.begin(16, 2);
  //lcd.blink();
  lcd.noBlink();
  //lcd.cursor();
  lcd.noCursor();
  //lcd.autoscroll();
  lcd.noAutoscroll();
  lcd.setCursor(0,0); // set to the 3th column and 2nd row
  lcd.print("Hello world ");// Print a message to the LCD.
  lcd.write(0);// Print a smiley
}

/*void pulseOut(int pin, int ms) {
  for (int i = 0; i < 20; i++) {
    digitalWrite(pin, HIGH);
    if (ms > 2600) {
      lcd.print(ms);
      ms = 2600;
    }
    delayMicroseconds(ms);
    digitalWrite(pin, LOW);
    delay(20);
  }
}

int angleToPulse(int alpha) {
  int max = 2600;
  int min = 200;
  float step = (max-min)/180.0;
  alpha = alpha%180;
  return min+alpha*step;
}*/

int knobToAngle(int pot) {
  int min = 0;
  int max = 1024;
  float step = 180.0/(max-min);
  return pot*step;
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  
  //lcd.print("");
  for(int i=1;i<6;i++) {
    analogValues[i-1] = analogRead(i);
    //lcd.print(i-1);
    //lcd.print(": "); 
    lcd.print(analogValues[i-1]);
    lcd.print(" ");
  }
  
  lcd.setCursor(0, 1);  
  for(int i=8;i<14;i++){
     lcd.print(digitalRead(i));
  }
  
  int angle = knobToAngle(analogValues[1]);
  //int pulse = angleToPulse(angle);
  //pulseOut(servoPin,pulse);
  servo.write(angle);
   
  // If Button turn LED on
  if (digitalRead(10) == HIGH) // if gas dense
  {
     digitalWrite(9,HIGH); // ring the Buzzer for alarm
  }
  else
  {
     digitalWrite(9,LOW); // turn off the buzzer
  }
  
  // Read ultra sounds value
  int ultraSoundSignal = 11; // Ultrasound signal pin
  pinMode(ultraSoundSignal, OUTPUT);

  /* Send low-high-low pulse to activate the trigger pulse of the sensor
   * -------------------------------------------------------------------
   */

  digitalWrite(ultraSoundSignal, LOW); // Send low pulse
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(ultraSoundSignal, HIGH); // Send high pulse
  delayMicroseconds(5); // Wait for 5 microseconds
  digitalWrite(ultraSoundSignal, LOW); // Holdoff
  
  /* Listening for echo pulse
   * -------------------------------------------------------------------
   */

  pinMode(ultraSoundSignal, INPUT); // Switch signalpin to input
  int val = digitalRead(ultraSoundSignal); // Append signal value to val
  while(val == LOW) { // Loop until pin reads a high value
    val = digitalRead(ultraSoundSignal);
  }
  
  int timecount = 0; // Echo counter
  while(val == HIGH) { // Loop until pin reads a low value
    val = digitalRead(ultraSoundSignal);
    timecount = timecount +1;            // Count echo pulse time
  }
  
  lcd.print(" U:");
  lcd.print(timecount);
    
  delay(500);
}

