#include <UltraSoundSignal.h>

long UltraSoundSignal::read() {
    // establish variables for duration of the ping, 
    // and the distance result in inches and centimeters:
    long duration;
    
    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(2);
    digitalWrite(pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pin, LOW);
    
    // The same pin is used to read the signal from the PING))): a HIGH
    // pulse whose duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(pin, INPUT);
    duration = pulseIn(pin, HIGH);
    
    
    oldDistance = distance;
    oldTime = time;
    
    // convert the time into a distance
    distance = centimeters(duration);
    time = millis();
    
    speed = (long)(((float)(distance - oldDistance)) / (((float)(time - oldTime)) / 1000));
    
    return distance;
}

long UltraSoundSignal::centimeters(long microseconds)
{
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    return microseconds / 29 / 2;
}

void UltraSoundSignal::registerListener(DistanceListener *listener) {
    this->listener = listener;
}

void UltraSoundSignal::signal() {
    read();
    listener->update(distance,speed,delay);
}
