#ifndef __STORAGE_H__
#define __STORAGE_H__


#include <Arduino.h>
#include <EEPROM.h>
#include "Constants.h"

#define PULSE_PER_MM_ADDRESS 2
#define STEP_PER_MM_ADDRESS 6
#define INVERT_STEPPER_DIR_ADDRESS 10
#define INVERT_ENCODER_DIR_ADDRESS 11
#define IS_UART_MODE_ADDRESS 12
#define IS_ENCODER_ABSOLUTE_MODE_ADDRESS 13
#define MAX_SPEED_ADDRESS 14
#define UUID_ADDRESS 18
#define DEVICE_MODEL_ADDRESS 38
#define FIRMWARE_VERSION_ADDRESS 58


class StorageClass
{
public:
    StorageClass();
    void init();
    void store_data();
    void get_data();
    void get(int idx, float &f);
    void put(int idx, const float &f);
    void get(int idx, bool &b);
    void put(int idx, const bool &b);
    void get(int idx, String &s);
    void put(int idx, const String &s);
    void get(int idx, unsigned long &l);
    void put(int idx, const unsigned long &l);
};

extern StorageClass Storage;

#endif // __STORAGE_H__