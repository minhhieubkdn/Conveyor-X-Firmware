#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <Arduino.h>
#include "Constants.h"
#include "fastio.h"

class EncoderClass
{
public:
    EncoderClass();
    void init();
    void setMode(bool mode);
    void getCurrentPosition();
    void setAutoReadPeriod(unsigned long period);
    void setPulsePerMM(float pulsePerMM);
    void setInvertDir(bool invertDir);
    void responsePositionISR();\
    void readEncoderISR();
    void execute();

    void setEncoderTimerPeriod(unsigned long period);

    int64_t absolute_pulse;
    bool is_absolute_mode;
    int64_t last_absolute_pulse;
    int32_t incremental_pulse;
    long encoder_period;
    long timer_counter;
    float pulse_per_mm;
    bool invert_encoder_dir;
    uint8_t timer2_loop_num;
    uint8_t timer2_loop_index;
    bool is_timer_enable;
};

extern EncoderClass Encoder;
#endif // __ENCODER_H__