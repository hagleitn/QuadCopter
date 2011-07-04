#include <AutoControl.h>

void AutoControl::update(double value) {
    
    double pTotal = 0;
    double iTotal = 0;
    double dTotal = 0;
    
    double error = goal - value;
    
    pTotal = proportional * error;   
    
    cummulativeError += error;
    if (cummulativeError > maxCummulative) {
        cummulativeError = maxCummulative;
    } else if (cummulativeError < minCummulative) {
        cummulativeError = minCummulative;
    }
    iTotal = integral * cummulativeError;
    
    dTotal = derivative * (value - lastValue);
    lastValue = value;
    
    control.adjust(pTotal + iTotal + dTotal);
}