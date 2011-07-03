#include <UltraSoundSignal.h>

bool UltraSoundSignal::read() {
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
    
    // convert the time into a distance
    int newDistance = centimeters(duration);

    // Serial.print("raw distance: ");
    // Serial.println(newDistance);

    if (newDistance > MAX_RELIABLE) {
        Serial.print(newDistance);
        Serial.println(" > than MAX_RELIABLE");
        newDistance = -1;
    }

    median.pushMeasurement(newDistance);
    bool success = median.getMedian(distance[index],time[index]);
    if (success) {
        //        Serial.print("median distance: (index: ");
        //	Serial.print(index);
        //        Serial.print(") ");
        //        Serial.println(distance[index]);

	//	  Serial.print("INDEX: ");
	//	  Serial.print(index);
	//	  Serial.print(", ");
        ++index;
        if (index >= size) {
            full = true;
            index %= size;
        }
	//	  Serial.println(index);
    }
    return success;
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

bool UltraSoundSignal::computeSpeed() {
    int oldest = index;
    int newest = (size+index-1)%size;
    if (!full || distance[oldest] == -1 || distance[newest] == -1 || (time[newest] - time[oldest]) < MIN_TIME_FOR_SPEED) {
        //Serial.print("time delta: (");
        //Serial.print(newest);
        //Serial.print(", ");
        //Serial.print(oldest);
        //Serial.print("): ");
        //Serial.println(time[newest] - time[oldest]);
      
        return false;
    }
    speed = (long)(((float)(distance[newest] - distance[oldest])) / (((float)(time[newest] - time[oldest])) / 1000));
    return true;
}

void UltraSoundSignal::signal() {
    if (read()) {
        if (computeSpeed()) {
	    // Serial.println("sending update...");
            int newest = (size+index-1)%size;
            listener->update(distance[newest],speed,time[newest]);
        }
    }
}
