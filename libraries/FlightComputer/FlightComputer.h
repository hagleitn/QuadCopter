#ifndef FLIGHT_COMPUTER_H
#define FLIGHT_COMPUTER_H

#include <WProgram.h>
#include <QuadCopter.h>
#include <AutoControl.h>
#include <SignalListener.h>
#include <RemoteControl.h>
#include <UltraSoundSignal.h>

class FlightComputer {
    
public:
    
    // Flight computer states
    typedef enum {GROUND=0, HOVER, LANDING, FAILED, EMERGENCY_LANDING, MANUAL_CONTROL} State;
    
    // values for the PID controller
    static const AutoControl::Configuration HOVER_CONF;
    static const AutoControl::Configuration LANDING_CONF;
    
    // delay between readings of the ultra sound module
    static const int MIN_TIME_ULTRA_SOUND = 100;
    
    // delay between status messages
    static const int MIN_TIME_STATUS_MESSAGE = 5000;
    
    // min/max for the automatic control of the throttle
    static const double MIN_THROTTLE = QuadCopter::MIN_SPEED/2;
    static const double MAX_THROTTLE = QuadCopter::MAX_SPEED/2;
    
    // landings will cut the power once this height is reached
    static const double THROTTLE_OFF_HEIGHT = 10;
    
    // throttle setting for when we don't know the height anymore
    static const int EMERGENCY_DESCENT = -20;
    
    FlightComputer(QuadCopter& ufo, RemoteControl &rc, UltraSoundSignal &ultraSound) : 
        ufo(ufo), rc(rc), ultraSound(ultraSound), throttleControl(ufo), heightListener(*this), autoThrottle(throttleControl), 
        state(GROUND), height(0), zeroHeight(0), time(0), lastTimeSignal(0), lastTimeLog(0) {};
    ~FlightComputer() {}
    
    void init();
    void takeoff(long);
    void hover(long);
    void land();
    void emergencyDescent();
    void manualControl();
    void abort();
    void adjust();
    void log();
    
private:
    
    // Listener to update the height of the flight computer
    class HeightListener : public SignalListener {
    public:
        HeightListener(FlightComputer &comp) : comp(comp) {};
        virtual void update(double x, long time) {
            comp.height = x;
        }
        FlightComputer &comp;
    };
    
    // adjusts output from PID controller for throttle setting
    class ThrottleControl : public ControlListener {
    public:
        ThrottleControl(QuadCopter &ufo) : ufo(ufo), currentThrottle(QuadCopter::MIN_SPEED) {};
        virtual void adjust(double x) {
            currentThrottle += x;
            if (currentThrottle > MAX_THROTTLE) {
                currentThrottle = MAX_THROTTLE;
            } else if (currentThrottle < MIN_THROTTLE) {
                currentThrottle = MIN_THROTTLE;
            }
            ufo.throttle((int)currentThrottle);
        }
        double currentThrottle;
        QuadCopter &ufo;
    };
    
    QuadCopter &ufo;
    RemoteControl &rc;
    UltraSoundSignal &ultraSound;
    ThrottleControl throttleControl;
    HeightListener heightListener;
    AutoControl autoThrottle;
    
    State state;
    double height;
    double zeroHeight;
    long time;
    long lastTimeSignal;
    long lastTimeLog;
};

#endif
