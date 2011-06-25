#include <QuadCopter.h>

void QuadCopter::arm() {
    // GAUI 330X good startup sound
    // beep-beep-beep[increse pitch] (3S)beep-beep-beep[quick] beep[LOW]
    stop(); // neutral state
    adjustGain(0); // initialize gain
    throttle(MIN_SPEED); //setting required to allow the 330X to start
}

QuadCopter::QuadCopter( 
                       int aileronPin, 
                       int rudderPin, 
                       int throttlePin, 
                       int elevatorPin, 
                       int gainPin) 
{
    pins[0] = elevatorPin;   // Red 
    pins[1] = aileronPin;    // White 
    pins[2] = throttlePin;   // Orange 
    pins[3] = rudderPin;     // Yellow 
    this->gainPin = gainPin; // Green (Gain/Gear) 
    speed[0] = speed[1] = speed[2] = speed[3] = 0;
}


void QuadCopter::attach() {
    for (int i = 0; i < DEGREES_OF_FREEDOM; ++i) {
        servos[i].attach(pins[i]);
    }
    gain.attach(gainPin);
}

void QuadCopter::init() {
    attach();
    arm();
}

void QuadCopter::adjustGain(int gainVal) {
    gain.write(map(gainVal, MIN_SPEED, MAX_SPEED, 0, 180));
}

void QuadCopter::stop(Direction d) {
    move(d,STOP_SPEED);
}

void QuadCopter::stop() {
    for (int i = 0; i < DEGREES_OF_FREEDOM; ++i) {
        stop((Direction)i);
    }
}

void QuadCopter::move(Direction d, int speed) {
    if (speed > MAX_SPEED) {
        speed = MAX_SPEED;
    } else if (speed < MIN_SPEED) {
        speed = MIN_SPEED;
    }
    
    Servo &s = this->servos[d];
    
    speed = map(speed ,MIN_SPEED, MAX_SPEED, 0, 180);   
    
    if (speed != s.read()) { 
        s.write(speed);
        this->speed[d] = speed; 
    }
}

void QuadCopter::move(int speeds[]) {
    for (int i = 0; i < DEGREES_OF_FREEDOM; ++i) {
        move((Direction)i, speeds[i]);
    }
}

void QuadCopter::move(int x, int y, int z, int r) {
    move(LONGITUDINAL, x); 
    move(LATERAL, y);
    move(VERTICAL, z);
    move(ROTATIONAL, r);
}
