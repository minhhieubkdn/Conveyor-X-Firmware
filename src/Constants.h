#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <Arduino.h>
#include "config.h"

class Constants
{
public:
    float max_speed = DEFAULT_MAX_SPEED;
    float speed = DEFAULT_SPEED;
    float step_per_mm = DEFAULT_STEP_PER_MM;
    float encoder_pulse_per_mm = DEFAULT_PULSE_PER_MM;
    unsigned long read_volume_time_ms = READ_VOLUME_TIME_MS;
    bool is_uart_mode = SERIAL_MODE;
    bool invert_stepper_dir = DEFAULT_INVERT_STEPPER_DIR;
    bool invert_encoder_dir = DEFAULT_INVERT_ENCODER_DIR;
    unsigned long encoder_period = DEFAULT_ENCODER_PERIOD;
    bool is_encoder_absolute_mode = DEFAULT_ENCODER_MODE_ABSOLUTE;

    String uuid = DEFAULT_UUID;
    String device_model = DEFAULT_DEVICE_MODEL;
    String firmware_version = DEFAULT_FIRMWARE_VERSION;

    bool is_data_stored = false;

};

extern Constants Data;

#endif // __CONSTANTS_H__