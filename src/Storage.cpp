#include "Storage.h"

StorageClass::StorageClass()
{
}

void StorageClass::init()
{
    EEPROM.begin();
    delay(10);
}

void StorageClass::store_data()
{
    Data.is_data_stored = true;
    EEPROM.write(0, Data.is_data_stored);
    delay(10);

    put(STEP_PER_MM_ADDRESS, Data.step_per_mm);
    put(PULSE_PER_MM_ADDRESS, Data.encoder_pulse_per_mm);
    put(INVERT_STEPPER_DIR_ADDRESS, Data.invert_stepper_dir);
    put(INVERT_ENCODER_DIR_ADDRESS, Data.invert_encoder_dir);
    put(IS_UART_MODE_ADDRESS, Data.is_uart_mode);
    put(IS_ENCODER_ABSOLUTE_MODE_ADDRESS, Data.is_encoder_absolute_mode);
    put(MAX_SPEED_ADDRESS, Data.max_speed);
    put(UUID_ADDRESS, Data.uuid);
    put(DEVICE_MODEL_ADDRESS, Data.device_model);
    put(FIRMWARE_VERSION_ADDRESS, Data.firmware_version);
}

void StorageClass::get_data()
{
    
    Data.is_data_stored = EEPROM.read(0);
    delay(10);

    get(STEP_PER_MM_ADDRESS, Data.step_per_mm);
    get(PULSE_PER_MM_ADDRESS, Data.encoder_pulse_per_mm);
    get(INVERT_STEPPER_DIR_ADDRESS, Data.invert_stepper_dir);
    get(INVERT_ENCODER_DIR_ADDRESS, Data.invert_encoder_dir);
    get(IS_UART_MODE_ADDRESS, Data.is_uart_mode);
    get(IS_ENCODER_ABSOLUTE_MODE_ADDRESS, Data.is_encoder_absolute_mode);
    get(MAX_SPEED_ADDRESS, Data.max_speed);
    get(UUID_ADDRESS, Data.uuid);
    get(DEVICE_MODEL_ADDRESS, Data.device_model);
    get(FIRMWARE_VERSION_ADDRESS, Data.firmware_version);
}

void StorageClass::get(int idx, float &f)
{
    for (int i = 0; i < sizeof(float); i++)
    {
        *((char *)&f + i) = EEPROM.read(idx + i);
    }
}

void StorageClass::put(int idx, const float &f)
{
    for (int i = 0; i < sizeof(float); i++)
    {
        EEPROM.write(idx + i, *((char *)&f + i));
    }
}

void StorageClass::get(int idx, bool &b)
{
    b = EEPROM.read(idx);
}

void StorageClass::put(int idx, const bool &b)
{
    EEPROM.write(idx, b);
}

void StorageClass::get(int idx, String &s)
{
    uint8_t len = EEPROM.read(idx);
    s = "";
    for (int i = 0; i < len; i++)
    {
        s += (char)EEPROM.read(idx + 1 + i);
    }
}

void StorageClass::put(int idx, const String &s)
{
    EEPROM.write(idx, s.length());
    for (int i = 0; i < s.length(); i++)
    {
        EEPROM.write(idx + 1 + i, s[i]);
    }
}

void StorageClass::get(int idx, unsigned long &l)
{
    for (int i = 0; i < sizeof(unsigned long); i++)
    {
        *((char *)&l + i) = EEPROM.read(idx + i);
    }
}

void StorageClass::put(int idx, const unsigned long &l)
{
    for (int i = 0; i < sizeof(unsigned long); i++)
    {
        EEPROM.write(idx + i, *((char *)&l + i));
    }
}

StorageClass Storage;