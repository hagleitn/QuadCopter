#include <UltraSoundSignal.h>

void UltraSoundSignal::setupMeasurement() {
    // The PING is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(2);
    digitalWrite(pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pin, LOW);
}    

bool UltraSoundSignal::convert(long microseconds, double& value)
{
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    value = microseconds / 29 / 2;
    return value <= MAX_RELIABLE;
}
