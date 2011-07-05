#include <FlightComputer.h>

const AutoControl::Configuration FlightComputer::HOVER_CONF   = { 0.05, 0.05, 0.1, -1000, 1000 };
const AutoControl::Configuration FlightComputer::LANDING_CONF = { 0.01, 0.005, 1, -1000, 1000 };

void FlightComputer::init() {
    ultraSound.registerListener(&heightListener); 
    ultraSound.registerListener(&autoThrottle);
}

void FlightComputer::takeoff(long centimeters) {
    if (state == GROUND) {
        state = HOVER;
        autoThrottle.setConfiguration(HOVER_CONF);
        autoThrottle.setGoal(centimeters);
        autoThrottle.engage(true);
    }
}

void FlightComputer::hover(long centimeters) {
    if (state == HOVER || state == LANDING) {
        state = HOVER;
        autoThrottle.setConfiguration(HOVER_CONF);
        autoThrottle.setGoal(centimeters);
    }
}

void FlightComputer::land() {
    if (state == HOVER || state == EMERGENCY_LANDING) {
        state = LANDING;
        autoThrottle.setGoal(zeroHeight);
        autoThrottle.setConfiguration(LANDING_CONF);
        autoThrottle.engage(true);
    }
}

void FlightComputer::emergencyDescent() {
    if (FAILED != state && GROUND != state) {
        autoThrottle.engage(false);
        ufo.throttle(EMERGENCY_DESCENT);
        state = EMERGENCY_LANDING;
    }
}

void FlightComputer::abort() {
    state = FAILED;
    autoThrottle.engage(false);
    ufo.throttle(QuadCopter::MIN_SPEED);
}

void FlightComputer::adjust() {
    time = millis();
    
    // allow for manual inputs first
    rc.update();
    
    // no height signal from ultra sound try descending
    if (-1 == height) { 
        emergencyDescent();
    } else {
        switch (state) {
            case GROUND:
                zeroHeight = height; // calibration
                break;
            case HOVER:
                // nothing
                break;
            case LANDING:
                // turn off throttle when close to ground
                if (height < zeroHeight + THROTTLE_OFF_HEIGHT) {
                    state = GROUND;
                    autoThrottle.engage(false);
                    ufo.throttle(QuadCopter::MIN_SPEED);
                }
                break;
            case EMERGENCY_LANDING:
                // We have entered emergency landing - but the height readings are back.
                // Let's just land.
                autoThrottle.engage(true);
                land();
                break;
            default:
                // this is bad
                land();
                break;
        }
    }
    
    if (time - lastTime > MIN_TIME_ULTRA_SOUND) {
        ultraSound.signal();
        lastTime = time;
    }
}
