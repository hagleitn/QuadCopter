#ifndef AUTO_CONTROL_H
#define AUTO_CONTROL_H

#include <WProgram.h>
#include <SignalListener.h>
#include <ControlListener.h>

class AutoControl : public SignalListener{
    
public:
    AutoControl(ControlListener &control, 
                double proportional, 
                double integral, 
                double derivative, 
                double minCummulative, 
                double maxCummulative,
                double initialGoal) : 
                control(control), 
                proportional(proportional), 
                integral(integral), 
                derivative(derivative),
                lastValue(0),
                cummulativeError(0),
                minCummulative(minCummulative), 
                maxCummulative(maxCummulative),
                goal(initialGoal) {};
    ~AutoControl(){};
    void init() {};
    
    virtual void update(double x);
    
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
    void setGoal(double goal) { this->goal = goal; cummulativeError = 0; lastValue = 0; }
    
private:
    
    ControlListener &control;
    double proportional;
    double integral;
    double derivative;
    double lastValue;
    double cummulativeError;
    double maxCummulative;
    double minCummulative;
    double goal;
};

#endif