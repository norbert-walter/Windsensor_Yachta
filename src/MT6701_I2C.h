/* 
 * Класс для Arduino IDE реализующий множество методов
 * взаимодействия с бесконтактным датчиком положения
 * MT6701 от компании MagnTek http://www.magntek.com.cn/en/index.htm
 * 
 * Документация к датчику:
 ** http://www.magntek.com.cn/en/list/177/559.htm
 ** http://www.magntek.com.cn/upload/MT6701_Rev.1.5.pdf
 * 
 * Контакты:
 ** GitHub - https://github.com/S-LABc
 ** Gmail - romansklyar15@gmail.com
 * 
 * Copyright (C) 2022. v1.2 / License MIT / Скляр Роман S-LAB
 */

#pragma once
#include "Arduino.h"
#include "Wire.h"

/*=== Настройки шины I2C датчика ===*/
const uint32_t MT6701_I2C_CLOCK_100KHZ = 100000;
const uint32_t MT6701_I2C_CLOCK_400KHZ = 400000;
const uint32_t MT6701_I2C_CLOCK_1MHZ   = 1000000;
const uint8_t MT6701_I2C_ADDRESS = 0x06;

/*=== Выводы MODE на разных платах (зависит от ядра) ===*/
#define STM32_MT6701_MODE_PIN   PC13
#define ESP8266_MT6701_MODE_PIN 2
#define ESP32_MT6701_MODE_PIN   4
#define ARDUINO_MT6701_MODE_PIN 3

/*=== Адреса регистров датчика ===*/
// Angle Data Register
const uint8_t MT6701_I2C_ANGLE_DATA_REG_H = 0x03;
const uint8_t MT6701_I2C_ANGLE_DATA_REG_L = 0x04;
// UVW_MUX только для корпуса QFN
const uint8_t MT6701_I2C_EEPROM_UVW_MUX_REG = 0x25;
const uint8_t MT6701_I2C_EEPROM_UVW_MUX_BIT = 7;
// ABZ_MUX
const uint8_t MT6701_I2C_EEPROM_ABZ_MUX_REG = 0x29;
const uint8_t MT6701_I2C_EEPROM_ABZ_MUX_BIT = 6;
// DIR
const uint8_t MT6701_I2C_EEPROM_DIR_REG = 0x29;
const uint8_t MT6701_I2C_EEPROM_DIR_BIT = 1;
// UVW_RES
const uint8_t MT6701_I2C_EEPROM_UVW_RES_REG   = 0x30;
const uint8_t MT6701_I2C_EEPROM_UVW_MUX_BIT_S = 4;
// ABZ_RES
const uint8_t MT6701_I2C_EEPROM_ABZ_RES_REG_H = 0x30;
const uint8_t MT6701_I2C_EEPROM_ABZ_RES_REG_L = 0x31;
const uint8_t MT6701_I2C_EEPROM_ABZ_MUX_BIT_S = 0;
// HYST
const uint8_t MT6701_I2C_EEPROM_HYST_REG_H = 0x32;
const uint8_t MT6701_I2C_EEPROM_HYST_REG_L = 0x34;
// Z_PULSE_WIDTH
const uint8_t MT6701_I2C_EEPROM_Z_PULSE_WIDTH_REG   = 0x32;
const uint8_t MT6701_I2C_EEPROM_Z_PULSE_WIDTH_BIT_S = 4;
// ZERO
const uint8_t MT6701_I2C_EEPROM_ZERO_REG_H = 0x32;
const uint8_t MT6701_I2C_EEPROM_ZERO_REG_L = 0x33;
// PWM_FREQ
const uint8_t MT6701_I2C_EEPROM_PWM_FREQ_REG = 0x38;
const uint8_t MT6701_I2C_EEPROM_PWM_FREQ_BIT = 7;
// PWM_POL
const uint8_t MT6701_I2C_EEPROM_PWM_POL_REG = 0x38;
const uint8_t MT6701_I2C_EEPROM_PWM_POL_BIT = 6;
// OUT_MODE
const uint8_t MT6701_I2C_EEPROM_OUT_MODE_REG = 0x38;
const uint8_t MT6701_I2C_EEPROM_OUT_MODE_BIT = 5;
// A_START
const uint8_t MT6701_I2C_EEPROM_A_START_REG_H = 0x3E;
const uint8_t MT6701_I2C_EEPROM_A_START_REG_L = 0x3F;
// A_STOP
const uint8_t MT6701_I2C_EEPROM_A_STOP_REG_H = 0x3E;
const uint8_t MT6701_I2C_EEPROM_A_STOP_REG_L = 0x40;
const uint8_t MT6701_I2C_EEPROM_A_STOP_BIT_S = 4;
// 7.2 EEPROM Programming
const uint8_t MT6701_I2C_EEPROM_PROG_KEY_REG   = 0x09;
const uint8_t MT6701_I2C_EEPROM_PROG_KEY_VALUE = 0xB3;
const uint8_t MT6701_I2C_EEPROM_PROG_CMD_REG   = 0x0A;
const uint8_t MT6701_I2C_EEPROM_PROG_CMD_VALUE = 0x05;

/*=== Вспомогательные значения ===*/
// Тип конфигурации выходного интерфейса (только для корпуса QFN)
enum MT6701I2CConfigurationOutputType {
  MT6701I2_CONFIG_OUTPUT_TYPE_UVW,
  MT6701I2_CONFIG_OUTPUT_TYPE_A_B_Z,
};
// Тип выходного интерфейса
enum MT6701I2COutputType {
  MT6701I2_OUTPUT_TYPE_ABZ,
  MT6701I2_OUTPUT_TYPE_UVW,
};
// Положительное направление вращения
enum MT6701I2CDirection {
  MT6701I2_DIRECTION_COUNTERCLOCKWISE, // Против часовй стрелки
  MT6701I2_DIRECTION_CLOCKWISE, // По часовой стрелке
};
// Ширина импульса Z
enum MT6701I2CZPulseWidth {
  MT6701I2_Z_PULSE_WIDTH_1LSB,
  MT6701I2_Z_PULSE_WIDTH_2LSB,
  MT6701I2_Z_PULSE_WIDTH_4LSB,
  MT6701I2_Z_PULSE_WIDTH_8LSB,
  MT6701I2_Z_PULSE_WIDTH_12LSB,
  MT6701I2_Z_PULSE_WIDTH_16LSB,
  MT6701I2_Z_PULSE_WIDTH_180DEG,
  MT6701I2_Z_PULSE_WIDTH_1LSB_2,
};
// Частота ШИМ
enum MT6701I2CFrequencyPWM {
  MT6701I2_PWM_FREQUENCY_9944,
  MT6701I2_PWM_FREQUENCY_4972,
};
// Полярность ШИМ
enum MT6701I2CPolarityPWM {
  MT6701I2_PWM_POLARITY_HIGH,
  MT6701I2_PWM_POLARITY_LOW,
};
// Режим выхода
enum MT6701I2COutputMode {
  MT6701I2_OUTPUT_MODE_ANALOG,
  MT6701I2_OUTPUT_MODE_PWM,
};
// Ответы стандартного вида успех/ошибка
const uint8_t MT6701I2C_DEFAULT_REPORT_ERROR = 0;
const uint8_t MT6701I2C_DEFAULT_REPORT_OK    = 1;
// Выбор интерфейсов датчика
const uint8_t MT6701I2C_MODE_I2C_SSI = 0;
const uint8_t MT6701I2C_MODE_UVW_ABZ = 1;


class MT6701I2C {
  private:
    TwoWire* _wire_; // Объект для использования методов I2C
    int8_t _pin_mode_ = -1; // Контакт микроконтроллера к которому подключен вывод MODE датчика

  protected:
    uint8_t MT_RequestSingleRegister(uint8_t _reg_addr); // Запрос значения регистра размером 1 байт
    void MT_WriteOneByte(uint8_t _reg_addr, uint8_t _payload); // Запись одного байта в однобайтовый регистр

  public:
    MT6701I2C(TwoWire* _twi); // Конструктор с использованием только интерфейса I2C

    void begin(void); // Вызов Wire.begin()
#if defined(ESP8266) || defined(ESP32)
    void begin(int8_t _sda_pin, int8_t _scl_pin); // Вызов Wire.begin(SDA, SCL) с указанием выводов
#endif
    void setClock(uint32_t _clock = MT6701_I2C_CLOCK_400KHZ); // Настройка частоты на 100кГц, 400кГц, 1МГц, или пользовательское значение (по умолчанию 400кГц)

    void saveNewValues(void); // Метод производителя для сохранения значений в памяти EEPROM. Рекомендуется выполнять при напряжение питания от 4.5В до 5.5В

    bool isConnected(void); // Проверка по стандартному алгоритму поиска устройств на линии I2C

    void attachModePin(byte _pin_mode); // Назначить контакт микроконтроллера для управления режимом интерфейса
    void detachModePin(void); // Освоободить назначенный контакт микроконтроллера для управления режимом интерфейса

    void enableI2CorSSI(void); // Включить интерфейс I2C/SSI. MT6701I2C_MODE_I2C_SSI
    void enableUVWorABZ(void); // Включить интерфейс UVW/ABZ. MT6701I2C_MODE_UVW_ABZ

    word getRawAngle(void); // Получить угол в чистом виде. 0 - 16383
    float getDegreesAngle(void); // Получить угол в градусах. 0.00 - 359.98
    float getRadiansAngle(void); // Получить угол в радианах. 0.00 - 6.28 

    MT6701I2CConfigurationOutputType getConfigurationOutputType(void); // Получить тип конфигурации выходного интерфейса (только для корпуса QFN). MT6701I2_CONFIG_OUTPUT_TYPE_UVW, MT6701I2_CONFIG_OUTPUT_TYPE_A_B_Z
    void setConfigurationOutputTypeABZ(void); // Установить тип конфигурации выходного интерфейса -A-B-Z (только для корпуса QFN)
    bool setConfigurationOutputTypeABZVerify(void); // То же самое, но с подтверждением (только для корпуса QFN)
    void setConfigurationOutputTypeUVW(void); // Установить тип конфигурации выходного интерфейса UVW (только для корпуса QFN)
    bool setConfigurationOutputTypeUVWVerify(void); // То же самое, но с подтверждением (только для корпуса QFN)

    MT6701I2COutputType getOutputType(void); // Получить тип выходного интерфейса. MT6701I2_OUTPUT_TYPE_ABZ, MT6701I2_OUTPUT_TYPE_UVW
    void setOutputTypeABZ(void); // Установить тип выходного интерфейса ABZ
    bool setOutputTypeABZVerify(void); // То же самое, но с подтверждением
    void setOutputTypeUVW(void); // Установить тип выходного интерфейса UVW
    bool setOutputTypeUVWVerify(void); // То же самое, но с подтверждением

    MT6701I2CDirection getOutputRotationDirection(void); // Получить направление вращения. MT6701I2_DIRECTION_COUNTERCLOCKWISE, MT6701I2_DIRECTION_CLOCKWISE
    void setOutputRotationDirectionCounterclockwise(void); // Установить направление вращения против часовой
    bool setOutputRotationDirectionCounterclockwiseVerify(void); // То же самое, но с подтверждением
    void setOutputRotationDirectionClockwise(void); // Установить направление вращения по часовой
    bool setOutputRotationDirectionClockwiseVerify(void); // То же самое, но с подтверждением

    byte getOutputResolutionUVW(void); // Получить значение выходного разрешения в режиме UVW. 1 - 16
    void setOutputResolutionUVW(byte _resolution); // Установить значение выходного разрешения в режиме UVW. 1 - 16
    bool setOutputResolutionUVWVerify(byte _resolution); // То же самое, но с подтверждением

    word getOutputResolutionABZ(void); // Получить значение выходного разрешения в режиме ABZ. 1 - 1024
    void setOutputResolutionABZ(word _resolution); // Установить значение выходного разрешения в режиме ABZ. 1 - 1024
    bool setOutputResolutionABZVerify(word _resolution); // То же самое, но с подтверждением

    MT6701I2CZPulseWidth getZPulseWidth(void); // Получить значение ширины импульса на контакте Z в режиме ABZ. MT6701I2_Z_PULSE_WIDTH_1LSB, MT6701I2_Z_PULSE_WIDTH_2LSB,
    // MT6701I2_Z_PULSE_WIDTH_4LSB, MT6701I2_Z_PULSE_WIDTH_8LSB, MT6701I2_Z_PULSE_WIDTH_12LSB, MT6701I2_Z_PULSE_WIDTH_16LSB, MT6701I2_Z_PULSE_WIDTH_180DEG, MT6701I2_Z_PULSE_WIDTH_1LSB_2,
    void setZPulseWidth1LSB(void); // Установить ширину импульса 1LSB
    bool setZPulseWidth1LSBVerify(void); // То же самое, но с подтверждением
    void setZPulseWidth2LSB(void); // Установить ширину импульса 2LSB
    bool setZPulseWidth2LSBVerify(void); // То же самое, но с подтверждением
    void setZPulseWidth4LSB(void); // Установить ширрину импульса 4LSB
    bool setZPulseWidth4LSBVerify(void); // То же самое, но с подтверждением
    void setZPulseWidth8LSB(void); // Установить ширину импульса 8LSB
    bool setZPulseWidth8LSBVerify(void); // То же самое, но с подтверждением
    void setZPulseWidth12LSB(void); // Установить ширину импульса 12LSB
    bool setZPulseWidth12LSBVerify(void); // То же самое, но с подтверждением
    void setZPulseWidth16LSB(void); // Установить ширину импульса 16LSB
    bool setZPulseWidth16LSBVerify(void); // То же самое, но с подтверждением
    void setZPulseWidth180DEG(void); // Установить ширину импульса 180 градсуов
    bool setZPulseWidth180DEGVerify(void); // То же самое, но с подтверждением

    word getZeroDegreePositionData(void); // Получить значение нулевого положения. Смотреть таблицу в документации стр 28. 0x000 - 0xFFF
    void setZeroDegreePositionData(word _zero_position_data); // Установить значение нулевого положения. Смотреть таблицу в документации
    bool setZeroDegreePositionDataVerify(word _zero_position_data); // То же самое, но с подтверждением

    MT6701I2CFrequencyPWM getFrequencyPWM(void); // Получить значение частоты ШИМ. MT6701I2_PWM_FREQUENCY_9944, MT6701I2_PWM_FREQUENCY_4972
    void setFrequencyPWM9944(void); // Установить частоту ШИМ 994.4Гц
    bool setFrequencyPWM9944Verify(void); // То же самое, но с подтверждением
    void setFrequencyPWM4972(void); // Установить частоту ШИМ 497.2Гц
    bool setFrequencyPWM4972Verify(void); // То же самое, но с подтверждением

    MT6701I2CPolarityPWM getPolarityPWM(void); // Получить значение полярности ШИМ. MT6701I2_PWM_POLARITY_HIGH, MT6701I2_PWM_POLARITY_LOW
    void setPolarityPWMHigh(void); // Установить полярность ШИМ HIGH
    bool setPolarityPWMHighVerify(void); // То же самое, но с подтверждением
    void setPolarityPWMLow(void); // Установить полярность ШИМ LOW
    bool setPolarityPWMLowVerify(void); // То же самое, но с подтверждением

    MT6701I2COutputMode getOutputMode(void); // Получить режима выхода. MT6701I2_OUTPUT_MODE_ANALOG, MT6701I2_OUTPUT_MODE_PWM
    void setOutputModeAnalog(void); // Установить режим выхода Аналог
    bool setOutputModeAnalogVerify(void); // То же самое, но с подтверждением
    void setOutputModePWM(void); // Установить режим выхода ШИМ
    bool setOutputModePWMVerify(void); // То же самое, но с подтверждением
};
