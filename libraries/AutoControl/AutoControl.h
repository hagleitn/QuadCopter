#ifndef AUTO_CONTROL_H
#define AUTO_CONTROL_H

#include <WProgram.h>
#include <SignalListener.h>
#include <ControlListener.h>

class AutoControl : public SignalListener{
    
public:
    
    typedef double Configuration[5];
        
    AutoControl(ControlListener &control) :
                control(control),
                proportional(0),
                integral(0),
                derivative(0),
                minCummulative(0),
                maxCummulative(0),
                lastValue(0),
                lastError(0),
                lastTime(0),
                isFirst(true),
                cummulativeError(0),
                goal(0),
                engaged(false) {};
    
    ~AutoControl(){};
    void init() {};
    
    virtual void update(double x, long time);
    
    void setConfiguration(const Configuration &conf);
    
    double getProportional() { return proportional; }
    void setProportional(double proportional) { this->proportional = proportional; }
    
    double getIntegral() { return integral; }
    void setIntegral(double integral) { this->integral = integral; }
    
    double getDerivative() { return derivative; }
    void setDerivative(double derivative) { this->derivative = derivative; }
    
    double getMaxCummulative() { return maxCummulative; }
    void setMaxCummulative(double max) { this->maxCummulative = max; }

    double getMinCummulative() { return minCummulative; }
    void setMinCummulative(double min) { this->minCummulative = min; }
    
    double getGoal() { return goal; }
    void setGoal(double goal) { this->goal = goal; isFirst = true; }
    
    void engage(bool engaged) { this->engaged = engaged; }
    bool isEngaged() { return engaged; }
    
private:
    
    ControlListener &control;
    double proportional;
    double integral;
    double derivative;
    double lastValue;
    double lastError;
    double lastTime;
    double cummulativeError;
    double maxCummulative;
    double minCummulative;
    double goal;
    bool engaged;
    bool isFirst;
};

#endif