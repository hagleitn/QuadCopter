void setup()
{
  pinMode(9,OUTPUT); //set the LED pin for digital output
  pinMode(8,INPUT); //set the tilt sensor pin for digital input  
}

void loop() {
  int valA1=0;
  //valA1 = analogRead(1);
  valA1 = digitalRead(8);
  //if (valA1>0x200) // if gas dense
  if (valA1 == HIGH)
  {
     digitalWrite(9,HIGH); // ring the Buzzer for alarm
  }
  else
  {
     digitalWrite(9,LOW); // turn off the buzzer
  }
    
  delay(100);
}

