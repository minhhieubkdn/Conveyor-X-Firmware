#include "Communication.h"

void EncoderISR()
{
    Encoder.readEncoderISR();
}

void StepperISR()
{
    Stepper.stepperISR();
}

void setup()
{
    Storage.init();
    Encoder.init();
    Stepper.init();
    Communication.init();
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), EncoderISR, CHANGE);
}

void loop()
{
    Communication.execute();
}