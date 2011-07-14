#include <AutoControl.h>

void AutoControl::setConfiguration(const Configuration &conf) {
    proportional = conf[0];
    integral = conf[1];
    derivative = conf[2];
    minCummulative = conf[3];
    maxCummulative = conf[4];
}

void AutoControl::update(double value, long time) {
        
    if (engaged) {
        
        if (isFirst) {
            isFirst = false;
            lastValue = value;
            lastTime = time;
            lastError = 0;
            cummulativeError = 0;
            return;
        }
                
        double pTotal = 0;
        double iTotal = 0;
        double dTotal = 0;
        
        double timeDelta = (lastTime - time);
        
        if (timeDelta == 0) {
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
        
        control.adjust(pTotal + iTotal + dTotal);
    }
}