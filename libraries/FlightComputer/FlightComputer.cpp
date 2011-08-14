#include <FlightComputer.h>

const AutoControl::Configuration FlightComputer::HOVER_CONF   = { 0.03, 0.005,  0.1, -1000,  1000 };
const AutoControl::Configuration FlightComputer::LANDING_CONF = { 0.01, 0.0005, 1,   -10000, 10000 };
const AutoControl::Configuration FlightComputer::ACCEL_CONF   = { 0.05, 0.05,   0.1, -100,   100 };

FlightComputer::FlightComputer(
        QuadCopter& ufo, 
        RemoteControl &rc, 
        UltraSoundSignal &ultraSound, 
        AccelerometerSignal &longitudinalAccel, 
        AccelerometerSignal &lateralAccel
    ) : 
    ufo(ufo), 
    rc(rc), 
    ultraSound(ultraSound), 
    throttleControl(ufo), 
    heightListener(*this), 
    autoThrottle(throttleControl),
    longitudinalAccel(longitudinalAccel), 
    elevatorControl(ufo), 
    longitudinalListener(*this), 
    autoElevator(elevatorControl),
    lateralAccel(lateralAccel), 
    aileronControl(ufo), 
    lateralListener(*this), 
    autoAileron(aileronControl),
    state(GROUND), 
    height(0), 
    zeroHeight(0), 
    longitudinalForce(0), 
    zeroLongitudinalForce(0), 
    lateralForce(0), 
    zeroLateralForce(0),
    time(0), 
    lastTimeHeightSignal(0),
    lastTimeAccelSignal(0),
    lastTimeLog(0)
{
    // set initial values to static conf arrays
    setHoverConfiguration(HOVER_CONF);
    setLandingConfiguration(LANDING_CONF);
    setStabilizerConfiguration(ACCEL_CONF);
};

void FlightComputer::init() {
    ultraSound.registerListener(&heightListener); 
    ultraSound.registerListener(&autoThrottle);
    longitudinalAccel.registerListener(&longitudinalListener);
    longitudinalAccel.registerListener(&autoElevator);
    lateralAccel.registerListener(&lateralListener);
    lateralAccel.registerListener(&autoAileron);
}

void FlightComputer::setHoverConfiguration(const AutoControl::Configuration &conf) {
    for (int i = 0; i < sizeof(AutoControl::Configuration)/sizeof(double); ++i) {
        hoverConf[i] = conf[i];
    }
}

void FlightComputer::setLandingConfiguration(const AutoControl::Configuration &conf) {
    for (int i = 0; i < sizeof(AutoControl::Configuration)/sizeof(double); ++i) {
        landingConf[i] = conf[i];
    }    
}

void FlightComputer::setStabilizerConfiguration(const AutoControl::Configuration &conf) {
    for (int i = 0; i < sizeof(AutoControl::Configuration)/sizeof(double); ++i) {
        accelConf[i] = conf[i];
    }
}

void FlightComputer::takeoff(long centimeters) {
    if (state == GROUND) {
        state = HOVER;
        autoThrottle.setConfiguration(hoverConf);
        autoThrottle.setGoal(centimeters);
        autoThrottle.engage(true);
    }
}

void FlightComputer::hover(long centimeters) {
    if (state == HOVER || state == LANDING || state == ENGAGING_AUTO_CONTROL) {
        state = HOVER;
        autoThrottle.setConfiguration(hoverConf);
        autoThrottle.setGoal(centimeters);
        autoThrottle.engage(true);
    }
}

void FlightComputer::land() {
    if (state == HOVER || state == EMERGENCY_LANDING) {
        state = LANDING;
        autoThrottle.setGoal(zeroHeight);
        autoThrottle.setConfiguration(landingConf);
        autoThrottle.engage(true);
    }
}

void FlightComputer::autoControl() {
    if (state == MANUAL_CONTROL) {
        state = ENGAGING_AUTO_CONTROL;
        
        // set rc to allow auto control of throttle
        char controlMask = rc.getControlMask();
        controlMask = controlMask & (~RemoteControl::THROTTLE_MASK);
        rc.setControlMask(controlMask);
        
        // disarm rc, so it doesn't immediately engage again
        rc.arm(false);
        
        // use current throttle setting and height for start values
        throttleControl.currentThrottle = ufo.read(QuadCopter::VERTICAL);
        hover(this->height);
    }
}

void FlightComputer::manualControl() {
    if (state != MANUAL_CONTROL) {
        autoThrottle.engage(false);
        stabilize(false);
        state = MANUAL_CONTROL;
    }
}

void FlightComputer::emergencyDescent() {
    if (FAILED != state && GROUND != state) {
        autoThrottle.engage(false);
        ufo.throttle(EMERGENCY_DESCENT);
        throttleControl.currentThrottle = EMERGENCY_DESCENT;
        state = EMERGENCY_LANDING;
    }
}

void FlightComputer::abort() {
    state = FAILED;
    autoThrottle.engage(false);
    stabilize(false);
    ufo.throttle(QuadCopter::MIN_SPEED);
    throttleControl.currentThrottle = QuadCopter::MIN_SPEED;
}

void FlightComputer::stabilize(bool engage) {
    char mask = RemoteControl::AILERON_MASK | RemoteControl::ELEVATOR_MASK;
    char controlMask = rc.getControlMask();
    
    if (engage) {
        controlMask = controlMask & ~mask;
    } else {
        controlMask = controlMask | mask;
        elevatorControl.currentElevator = QuadCopter::STOP_SPEED;
        aileronControl.currentAileron = QuadCopter::STOP_SPEED;
    }
    rc.setControlMask(controlMask);
    
    autoElevator.setConfiguration(accelConf);
    autoAileron.setConfiguration(accelConf);
    autoElevator.setGoal(zeroLongitudinalForce);
    autoAileron.setGoal(zeroLateralForce);
    autoElevator.engage(engage);
    autoAileron.engage(engage);
}

void FlightComputer::log() {
    Serial.print("st: ");
    Serial.print(state);
    Serial.print(", ms: ");
    Serial.print(time);
    Serial.print(", rc: ");
    Serial.println((byte)rc.getControlMask(),BIN);
    Serial.print("h: ");
    Serial.print(height-zeroHeight);
    Serial.print(", y'': ");
    Serial.print(longitudinalForce-zeroLongitudinalForce);
    Serial.print(", x'': ");
    Serial.println(lateralForce-zeroLateralForce);
    Serial.print("t: ");
    Serial.print(throttleControl.currentThrottle);
    Serial.print(", e: ");
    Serial.print(elevatorControl.currentElevator);
    Serial.print(", a: ");
    Serial.println(aileronControl.currentAileron);
    Serial.println();
}

int FlightComputer::limit(const double value, const int min, const int max) {
    return (int)(value < min ? min : (value > max ? max : value));
}

void FlightComputer::adjust() {
    time = millis();
    
    // allow for manual inputs first
    rc.update();
    if (rc.getControlMask() == RemoteControl::FULL_MANUAL) {
        manualControl();
    }

    // no height signal from ultra sound try descending
    if (-1 == height) { 
        emergencyDescent();
    } else {
        switch (state) {
            case GROUND:
                // calibration
                zeroHeight = height;
                zeroLongitudinalForce = longitudinalForce;
                zeroLateralForce = lateralForce;
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
                    throttleControl.currentThrottle = QuadCopter::MIN_SPEED;
                }
                break;
            case EMERGENCY_LANDING:
                // We have entered emergency landing - but the height readings are back.
                // Let's just land.
                autoThrottle.engage(true);
                land();
                break;
            case MANUAL_CONTROL:
                // nothing
                break;
            case FAILED:
                // nothing
                break;
            case ENGAGING_AUTO_CONTROL:
                // nothing
                break;
            default:
                // this is bad
                land();
                break;
        }
    }
    
    if (time - lastTimeHeightSignal > MIN_TIME_ULTRA_SOUND) {
        ultraSound.signal();
        lastTimeHeightSignal = time;
    }
    
    if (time -lastTimeLog > MIN_TIME_STATUS_MESSAGE) {
        log();
        lastTimeLog = time;
    }
    
    if (time - lastTimeAccelSignal > MIN_TIME_ACCEL) {
        longitudinalAccel.signal();
        lateralAccel.signal();
        lastTimeAccelSignal = time;
    }
}
