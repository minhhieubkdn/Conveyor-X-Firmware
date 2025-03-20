#include "Stepper.h"

StepperClass::StepperClass()
{
}

void StepperClass::init()
{
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    digitalWrite(EN_PIN, 0);

    initStepperTimer();
}

void StepperClass::setSpeed(float speed)
{
    StopStepperTimer;
    desired_speed = speed;
    setStepperTimerPeriod(SPEED_TO_CYCLE(speed));
    is_timer_enabled = true;
    ResumeStepperTimer;
}

void StepperClass::setDesirePosition(float position)
{
    StopStepperTimer;
    desired_position = position;
    
}

void StepperClass::setPositionSpeed(float speed)
{
    position_speed = speed;
}

void StepperClass::setStepPerMM(float stepPerMM)
{
    Data.step_per_mm = stepPerMM;
}

void StepperClass::setMode(bool mode)
{
    Data.is_uart_mode = mode;
}

void StepperClass::setInvertDir(bool invertDir)
{
    digitalWrite(DIR_PIN, invertDir);
}

void StepperClass::setStepperEnable(bool enable)
{
    digitalWrite(EN_PIN, enable);
}

void StepperClass::stepperISR()
{
    digitalWrite(STEP_PIN, 0);
    delayMicroseconds(2);
    digitalWrite(STEP_PIN, 1);

    if (desired_step != 0)
    {
        current_step++;
        if (desired_step == current_step)
        {
            COMMAND_PORT.println("Ok");
            StopStepperTimer;
            desired_step = 0;
            current_step = 0;
        }
    }
}

void StepperClass::execute()
{
    desired_speed = abs(desired_speed);
    setStepperTimerPeriod(SPEED_TO_CYCLE(desired_speed));
    desired_step += roundf(desired_position * DEFAULT_STEP_PER_MM);
    desired_position = 0;
}

void StepperClass::setStepperTimerPeriod(float period)
{
    int prescaler;

    if (period > 4000)
    {
        TCCR1B |= (1 << CS11);
        TCCR1B &= ~(1 << CS10);
        prescaler = 8;
    }
    else
    {
        TCCR1B &= ~(1 << CS11);
        TCCR1B |= (1 << CS10);
        prescaler = 1;
    }

    STEPPER_COMPARE_VALUE_TIMER = roundf(period * F_CPU / (1000000.0 * prescaler)) - 1;
}

void StepperClass::resetParameters()
{
    desired_speed = 0;
    desired_position = 0;
    desired_step = 0;
    current_step = 0;
    position_speed = 0;
    Data.is_uart_mode = SERIAL_MODE;
}

void StepperClass::initStepperTimer()
{
    noInterrupts();

    // Reset register relate to Timer 1
    // Reset register relate
    TCCR1A = TCCR1B = TCNT1 = 0;
    // Set CTC mode to Timer 1
    TCCR1B |= (1 << WGM12);
    // Set prescaler 1 to Timer 1
    TCCR1B |= (1 << CS10);
    // Normal port operation, OCxA disconnected
    TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0));

    interrupts();

    StopStepperTimer;
}

int StepperClass::readPotentiometer()
{
    int potValue = analogRead(VOLUME_PIN);
    return potValue;
}

StepperClass Stepper;