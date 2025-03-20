#ifndef __STEPPER_H__
#define __STEPPER_H__

#include <Arduino.h>
#include "Constants.h"

class StepperClass
{
public:
    StepperClass();
    void init();
    void setSpeed(float speed);
    void setDesirePosition(float position);
    void setPositionSpeed(float speed);
    void setStepPerMM(float stepPerMM);
    void setMode(bool mode);
    void setInvertDir(bool invertDir);
    void setStepperEnable(bool enable);
    void stepperISR();
    void execute();

private:
    void setStepperTimerPeriod(float period);
    void resetParameters();
    void initStepperTimer();
    int readPotentiometer();

    float desired_speed;
    float desired_position;
    long desired_step;
    long current_step;
    float position_speed;
    bool is_timer_enabled;

};

extern StepperClass Stepper;
#endif // __STEPPER_H__