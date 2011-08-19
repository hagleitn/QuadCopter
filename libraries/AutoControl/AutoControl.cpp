#include <AutoControl.h>

void AutoControl::setConfiguration(const Configuration &conf) {
    proportional = conf[0];
    integral = conf[1];
    derivative = conf[2];
    minCummulative = conf[3];
    maxCummulative = conf[4];
    isFirst = true;
}

void AutoControl::update(double value, long time) {
    
    if (engaged) {
        
        if (isFirst) {
            isFirst = false;
            lastValue = value;
            lastTime = time;
            lastError = goal - value;
            cummulativeError = 0;
            return;
        }
                
        double pTotal = 0;
        double iTotal = 0;
        double dTotal = 0;
        
        double timeDelta = time - lastTime;
        
        if (timeDelta <= 0) {
            return;
        }
        
        double error = goal - value;
        double errorDelta = (error - lastError);
     
        // simple adjustment proportional to the error
        pTotal = proportional * error;
        
        // reacts to the length of an error
        cummulativeError += error * timeDelta;
        if (cummulativeError > maxCummulative) {
            cummulativeError = maxCummulative;
        } else if (cummulativeError < minCummulative) {
            cummulativeError = minCummulative;
        }
        iTotal = integral * cummulativeError;
        
        // adjustment to react to the closing speed
        dTotal = derivative * (errorDelta / timeDelta);
        
        lastValue = value;
        lastError = error;
        lastTime = time;
        
        /*Serial.print(time);
        Serial.print("\t");
        Serial.print(value);
        Serial.print("\t");
        Serial.print(pTotal);
        Serial.print("\t");
        Serial.print(iTotal);
        Serial.print("\t");
        Serial.print(dTotal);
        Serial.print("\t");
        Serial.print(pTotal+iTotal+dTotal);
        Serial.print("\t");
        Serial.print(error);
        Serial.print("\t");
        Serial.println(cummulativeError);*/
                
        control.adjust(pTotal + iTotal + dTotal);
    }
}