#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "pin.h"

#define DEFAULT_UUID "0000-0000-0000-0001"
#define DEFAULT_DEVICE_MODEL "DesktopConveyorX"
#define DEFAULT_FIRMWARE_VERSION "1.0.0"

#define STEPPER_COMPARE_VALUE_TIMER OCR1A
#define ResumeStepperTimer (TIMSK1 |= (1 << OCIE1A))
#define StopStepperTimer (TIMSK1 &= ~(1 << OCIE1A))

#define READ_VOLUME_TIME_MS 10

#define SERIAL_MODE true
#define VOLUME_MODE false

#define COMMAND_PORT Serial

#define DEFAULT_MAX_SPEED 600
#define DEFAULT_SPEED 30

#define DEFAULT_STEP_PER_MM 78.3532
#define SPEED_TO_CYCLE(x) (1000000.0 / (DEFAULT_STEP_PER_MM * x))
#define DEFAULT_INVERT_STEPPER_DIR false

#define DEFAULT_PULSE_PER_MM 10.24f
#define DEFAULT_ENCODER_PERIOD 100
#define DEFAULT_INVERT_ENCODER_DIR false
#define DEFAULT_ENCODER_MODE_ABSOLUTE true

#define ResumeEncoderTimer (TIMSK2 |= (1 << OCIE2A))
#define StopEncoderTimer (TIMSK2 &= ~(1 << OCIE2A))

#endif // __CONFIG_H__