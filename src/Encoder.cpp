#include "Encoder.h"

EncoderClass::EncoderClass()
{
}

void EncoderClass::init()
{
    pinMode(ENCODER_PIN_A, INPUT);
    pinMode(ENCODER_PIN_B, INPUT);

    setEncoderTimerPeriod(1000);
}



void EncoderClass::responsePositionISR()
{
    if (!is_timer_enable)
        return;

    if (timer2_loop_index == timer2_loop_num)
    {
        timer2_loop_index = 1;

        timer_counter += 1;
        if (timer_counter == encoder_period)
        {
            timer_counter = 0;
            getCurrentPosition();
        }
    }
    else
    {
        timer2_loop_index++;
    }
}

void EncoderClass::readEncoderISR()
{
    if (READ(ENCODER_PIN_B) == invert_encoder_dir)
    {
        if (READ(ENCODER_PIN_A) == invert_encoder_dir)
        {
            absolute_pulse--;
        }
        else
        {
            absolute_pulse++;
        }
    }
    else
    {
        if (READ(ENCODER_PIN_A) == invert_encoder_dir)
        {
            absolute_pulse++;
        }
        else
        {
            absolute_pulse--;
        }
    }
}

void EncoderClass::setMode(bool mode)
{
    is_absolute_mode = mode;
}

void EncoderClass::getCurrentPosition()
{
    if (is_absolute_mode)
    {
        COMMAND_PORT.println(absolute_pulse / pulse_per_mm, 3);
    }
    else
    {
        incremental_pulse = absolute_pulse - last_absolute_pulse;
        last_absolute_pulse = absolute_pulse;
        COMMAND_PORT.println(incremental_pulse / pulse_per_mm, 3);
    }
}

void EncoderClass::setAutoReadPeriod(unsigned long period)
{
    encoder_period = period;
}

void EncoderClass::setPulsePerMM(float pulsePerMM)
{
    pulse_per_mm = pulsePerMM;
}

void EncoderClass::setInvertDir(bool invertDir)
{
    invert_encoder_dir = invertDir;
}

void EncoderClass::setEncoderTimerPeriod(unsigned long period)
{
    noInterrupts();

    TCCR2A = TCCR2B = TCNT2 = 0;
    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS20);

    interrupts();
    StopEncoderTimer;

    int prescaler;
    if (period < 16)
    {
        TCCR2B |= (1 << CS20);
        TCCR2B &= ~(1 << CS22);
        prescaler = 1;
        timer2_loop_num = 1;
        OCR2A = roundf(period * 16 / prescaler - 1);
    }
    else if (period < 1020)
    {
        TCCR2B |= (1 << CS22);
        TCCR2B &= ~(1 << CS20);
        prescaler = 64;
        timer2_loop_num = 1;
        OCR2A = roundf(period * 16 / prescaler - 1);
    }
    else
    {
        TCCR2B |= (1 << CS22);
        TCCR2B &= ~(1 << CS20);
        prescaler = 64;
        timer2_loop_num = period / 1000 + 1;
        OCR2A = roundf((period / timer2_loop_num) * 16 / prescaler - 1);
    }
    ResumeEncoderTimer;
}

EncoderClass Encoder;