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

#include "MT6701_I2C.h"

// ########## CONSTRUCTOR ##########
/*
 * @brief: использовать только интерфейс I2C
 * @param _twi: доступ к методам объекта Wire
 */
MT6701I2C::MT6701I2C(TwoWire* _twi) : _wire_(_twi ? _twi : &Wire) {
  // Ничего
}
/* 
 * @brief: запросить один байт данных из буфера
 * @param _reg_addr: 1 байт адреса регистра
 * @return: значение байта из регистра, который был запрошен
 * @note: использовать для одиночного регистра, например 0x29
 */
uint8_t MT6701I2C::MT_RequestSingleRegister(uint8_t _reg_addr) {
  uint8_t single_byte = 0;

  // Начать передачу по адресу
  _wire_->beginTransmission(MT6701_I2C_ADDRESS);
  // Отправить байт регистра
  _wire_->write(_reg_addr);
  // Завершить соединение
  _wire_->endTransmission();
  
  // Запросить байт данных по адресу
  _wire_->requestFrom(MT6701_I2C_ADDRESS, (uint8_t)1);
  // Прочитать данные из буфера
  if (_wire_->available() >= 1 ) {
    single_byte = _wire_->read();
  }
  // Завершить соединение
  _wire_->endTransmission();

  return single_byte;
}
/*
 * @brief: записать значение размером 1 байт в произвольный регистр размером 1 байт
 * @param _reg_addr: 1 байт адреса регистра
 * @param _payload: 1 байт полезных данных
 */
void MT6701I2C::MT_WriteOneByte(uint8_t _reg_addr, uint8_t _payload) {
  // Начать передачу по адресу для прередачи байта данных в регистр
  _wire_->beginTransmission(MT6701_I2C_ADDRESS);
  _wire_->write(_reg_addr);
  _wire_->write(_payload);
  // Завершить соединение
  _wire_->endTransmission();
}

// ########## PUBLIC ##########
/* 
 * @brief: вызов метода Wire.begin()
 * @note: использовать, если действие не было выполнено ранее
 */
void MT6701I2C::begin(void) {
  _wire_->begin();
}
/* 
 * @brief: вызов метода Wire.begin(SDA, SCL) с указанием выводов
 * @param _sda_pin: пользовательский контакт SDA
 * @param _scl_pin: пользовательский контакт SCL
 * @note: использовать, если действие не было выполнено ранее.
 *   Применимо для платформ на базе ESP8266 и ESP32
 */
#if defined(ESP8266) || defined(ESP32)
void MT6701I2C::begin(int8_t _sda_pin, int8_t _scl_pin) {
  _wire_->begin(_sda_pin, _scl_pin);
}
#endif
/* 
 * @brief: настройка произвольной частоты шины I2C (по умолчанию 400кГц)
 * @note: использовать, если частота шины меняется из-за разных устройств
 */
void MT6701I2C::setClock(uint32_t _clock) {
  _wire_->setClock(_clock);
}
/*
 * @brief: сохраняет данные в EEPROM памяти датчика
 * @note: назначение каждой команды не описано в документации, порядок команд описан в 7.2 EEPROM Programming
 *  рекомендуется выполнять эту операцию при напряжении питания от 4.5В до 5.5В
 */
void MT6701I2C::saveNewValues(void) {
  // Начать передачу по адресу
  _wire_->beginTransmission(MT6701_I2C_ADDRESS);
  // Отправить 0x09
  _wire_->write(MT6701_I2C_EEPROM_PROG_KEY_REG);
  // Отправить 0xB3
  _wire_->write(MT6701_I2C_EEPROM_PROG_KEY_VALUE);
  // Завершить соединение
  _wire_->endTransmission();
  
  // Начать передачу по адресу
  _wire_->beginTransmission(MT6701_I2C_ADDRESS);
  // Отправить 0x0A
  _wire_->write(MT6701_I2C_EEPROM_PROG_CMD_REG);
  // Отправить 0x05
  _wire_->write(MT6701_I2C_EEPROM_PROG_CMD_VALUE);
  // Завершить соединение
  _wire_->endTransmission();
}
/*
 * @brief: узнать подкючен ли датчик к линии I2C
 * @note: используется алгоритм стандартного поиска устройств на шина I2C
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не подключен
 *  MT6701I2C_DEFAULT_REPORT_OK - подключен
 */
bool MT6701I2C::isConnected(void) {
  // Начать передачу по адресу
  _wire_->beginTransmission(MT6701_I2C_ADDRESS);
  return (!_wire_->endTransmission(MT6701_I2C_ADDRESS)) ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/*
 * @brief: назначить контакт микроконтроллера для управления режимом интерфейса
 * @param _pin_mode: контакт микроконтроллера к которому подключен контакт MODE датчика
 */
void MT6701I2C::attachModePin(byte _pin_mode) {
  _pin_mode_ = _pin_mode;
  pinMode(_pin_mode_, OUTPUT);
}
/*
 * @brief: освоободить назначенный контакт микроконтроллера для управления режимом интерфейса
 */
void MT6701I2C::detachModePin(void) {
  pinMode(_pin_mode_, INPUT);
  _pin_mode_ = -1;
}
/* 
 * @brief: включить интерфейс I2C/SSI
 */
void MT6701I2C::enableI2CorSSI(void) {
  digitalWrite(_pin_mode_, MT6701I2C_MODE_I2C_SSI);
}
/* 
 * @brief: включить интерфейс UVW/ABZ
 */
void MT6701I2C::enableUVWorABZ(void) {
  digitalWrite(_pin_mode_, MT6701I2C_MODE_UVW_ABZ);
}
/* 
 * @brief: получить чистое значение угла из Angle Data Register(13:0)
 * @return:
 *  0 - 16383
 */
word MT6701I2C::getRawAngle(void) {
  uint8_t high_byte = MT_RequestSingleRegister(MT6701_I2C_ANGLE_DATA_REG_H);
  uint8_t low_byte = MT_RequestSingleRegister(MT6701_I2C_ANGLE_DATA_REG_L);
  return (word)(high_byte << 6) | (low_byte >> 2);
}
/* 
 * @brief: получить значение угла в градусах
 * @return:
 *  0.00 - 359.98
 */
float MT6701I2C::getDegreesAngle(void) {
  return ((float)getRawAngle() * 360) / 16384;
}
/* 
 * @brief: получить значение угла в радианах
 * @return:
 *  0.00 - 6.28319
 */
float MT6701I2C::getRadiansAngle(void) {
  return (getDegreesAngle() * M_PI) / 180;
}
/* 
 * @brief: получить тип конфигурации выходного интерфейса
 * @note: только для корпуса QFN
 * @return:
 *  MT6701I2_OUTPUT_TYPE_A_B_Z
 *  MT6701I2_OUTPUT_TYPE_UVW
 */
MT6701I2CConfigurationOutputType MT6701I2C::getConfigurationOutputType(void) {
  return (MT6701I2CConfigurationOutputType)((MT_RequestSingleRegister(MT6701_I2C_EEPROM_UVW_MUX_REG) >> MT6701_I2C_EEPROM_UVW_MUX_BIT) & 0x01);
}
/* 
 * @brief: установить тип конфигурации выходного интерфейса -A-B-Z
 * @note: только для корпуса QFN
 */
void MT6701I2C::setConfigurationOutputTypeABZ(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_UVW_MUX_REG);
  bkup &= ~(1 << MT6701_I2C_EEPROM_UVW_MUX_BIT);
  MT_WriteOneByte(MT6701_I2C_EEPROM_UVW_MUX_REG, bkup);
}
/* 
 * @brief: установить тип конфигурации выходного интерфейса -A-B-Z с проверкой
 * @note: только для корпуса QFN
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setConfigurationOutputTypeABZVerify(void) {
  setConfigurationOutputTypeABZ();
  return getConfigurationOutputType() ? MT6701I2C_DEFAULT_REPORT_ERROR : MT6701I2C_DEFAULT_REPORT_OK;
}
/* 
 * @brief: установить тип конфигурации выходного интерфейса UVW
 * @note: только для корпуса QFN
 */
void MT6701I2C::setConfigurationOutputTypeUVW(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_UVW_MUX_REG);
  bkup |= 1 << MT6701_I2C_EEPROM_UVW_MUX_BIT;
  MT_WriteOneByte(MT6701_I2C_EEPROM_UVW_MUX_REG, bkup);
}
/* 
 * @brief: установить тип конфигурации выходного интерфейса UVW с проверкой
 * @note: только для корпуса QFN
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setConfigurationOutputTypeUVWVerify(void) {
  setConfigurationOutputTypeUVW();
  return getConfigurationOutputType() ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/* 
 * @brief: получить значение типа выходного интерфейса
 * @return:
 *  MT6701I2_OUTPUT_TYPE_ABZ
 *  MT6701I2_OUTPUT_TYPE_UVW
 */
MT6701I2COutputType MT6701I2C::getOutputType(void) {
  return (MT6701I2COutputType)((MT_RequestSingleRegister(MT6701_I2C_EEPROM_ABZ_MUX_REG) >> MT6701_I2C_EEPROM_ABZ_MUX_BIT) & 0x01);
}
/* 
 * @brief: установить тип выходного интерфейса ABZ
 */
void MT6701I2C::setOutputTypeABZ(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_ABZ_MUX_REG);
  bkup &= ~(1 << MT6701_I2C_EEPROM_ABZ_MUX_BIT);
  MT_WriteOneByte(MT6701_I2C_EEPROM_ABZ_MUX_REG, bkup);
}
/* 
 * @brief: установить тип выходного интерфейса ABZ с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setOutputTypeABZVerify(void) {
  setOutputTypeABZ();
  return getOutputType() ? MT6701I2C_DEFAULT_REPORT_ERROR : MT6701I2C_DEFAULT_REPORT_OK;
}
/* 
 * @brief: установить тип выходного интерфейса UVW
 */
void MT6701I2C::setOutputTypeUVW(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_ABZ_MUX_REG);
  bkup |= 1 << MT6701_I2C_EEPROM_ABZ_MUX_BIT;
  MT_WriteOneByte(MT6701_I2C_EEPROM_ABZ_MUX_REG, bkup);
}
/* 
 * @brief: установить тип выходного интерфейса UVW с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setOutputTypeUVWVerify(void) {
  setOutputTypeUVW();
  return getOutputType() ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/* 
 * @brief: получить значение положительного направления вращения
 * @return:
 *  MT6701I2_DIRECTION_COUNTERCLOCKWISE
 *  MT6701I2_DIRECTION_CLOCKWISE
 */
MT6701I2CDirection MT6701I2C::getOutputRotationDirection(void) {
  return (MT6701I2CDirection)((MT_RequestSingleRegister(MT6701_I2C_EEPROM_DIR_REG) >> MT6701_I2C_EEPROM_DIR_BIT) & 0x01);
}
/* 
 * @brief: установить положительное направление вращения против часовой стрелки
 */
void MT6701I2C::setOutputRotationDirectionCounterclockwise(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_DIR_REG);
  bkup &= ~(1 << MT6701_I2C_EEPROM_DIR_BIT);
  MT_WriteOneByte(MT6701_I2C_EEPROM_DIR_REG, bkup);
}
/* 
 * @brief: установить положительное направление вращения против часовой стрелки с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setOutputRotationDirectionCounterclockwiseVerify(void) {
  setOutputRotationDirectionCounterclockwise();
  return getOutputRotationDirection() ? MT6701I2C_DEFAULT_REPORT_ERROR : MT6701I2C_DEFAULT_REPORT_OK;
}
/* 
 * @brief: установить положительное направление вращения по часовой стрелке
 */
void MT6701I2C::setOutputRotationDirectionClockwise(void) {
  uint8_t bkup =MT_RequestSingleRegister(MT6701_I2C_EEPROM_DIR_REG);
  bkup |= 1 << MT6701_I2C_EEPROM_DIR_BIT;
  MT_WriteOneByte(MT6701_I2C_EEPROM_DIR_REG, bkup);
}
/* 
 * @brief: установить положительное направление вращения по часовой стрелке с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setOutputRotationDirectionClockwiseVerify(void) {
  setOutputRotationDirectionClockwise();
  return getOutputRotationDirection() ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/* 
 * @brief: получить значение выходного разрешения в режиме UVW
 * @return:
 *  1 - 16
 */
byte MT6701I2C::getOutputResolutionUVW(void) {
  return ((MT_RequestSingleRegister(MT6701_I2C_EEPROM_UVW_RES_REG) >> MT6701_I2C_EEPROM_UVW_MUX_BIT_S) & 0x0F) + 1; // 0x0F = 0b00001111, +1 для смещения в диапазон 1-16
}
/* 
 * @brief: установить значение выходного разрешения в режиме UVW
 * @param _resolution:
 *  1 - 16
 */
void MT6701I2C::setOutputResolutionUVW(byte _resolution) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_UVW_RES_REG);
  bkup |= (_resolution - 1) << MT6701_I2C_EEPROM_UVW_MUX_BIT_S; // -1 для смещения в диапазон 0-15
  MT_WriteOneByte(MT6701_I2C_EEPROM_UVW_RES_REG, bkup);
}
/* 
 * @brief: установить значение выходного разрешения в режиме UVW с проверкой
 * @param _resolution:
 *  1 - 16
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setOutputResolutionUVWVerify(byte _resolution) {
  setOutputResolutionUVW(_resolution);
  return getOutputResolutionUVW() == _resolution ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/* 
 * @brief: получить значение выходного разрешения в режиме ABZ
 * @return:
 *  1 - 1024
 */
word MT6701I2C::getOutputResolutionABZ(void) {
  uint8_t reg_h = MT_RequestSingleRegister(MT6701_I2C_EEPROM_ABZ_RES_REG_H) & 0x03; // 0x03 = 0b00000011
  return (word)((reg_h << 8) | MT_RequestSingleRegister(MT6701_I2C_EEPROM_ABZ_RES_REG_L)) + 1; // +1 для смещения в диапазон 1-1024
}
/* 
 * @brief: установить значение выходного разрешения в режиме ABZ
 * @param _resolution:
 *  1 - 1024
 */
void MT6701I2C::setOutputResolutionABZ(word _resolution) {
  uint8_t reg_l = (_resolution - 1) & 0xFF;
  uint8_t reg_h = MT_RequestSingleRegister(MT6701_I2C_EEPROM_ABZ_RES_REG_H);
  reg_h |= ((_resolution - 1) >> 8) & 0x03;
  MT_WriteOneByte(MT6701_I2C_EEPROM_ABZ_RES_REG_H, reg_h);
  MT_WriteOneByte(MT6701_I2C_EEPROM_ABZ_RES_REG_L, reg_l);
}
/* 
 * @brief: установить значение выходного разрешения в режиме ABZ с проверкой
 * @param _resolution:
 *  1 - 1024
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setOutputResolutionABZVerify(word _resolution) {
  setOutputResolutionABZ(_resolution);
  return getOutputResolutionABZ() == _resolution ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}


/* 
 * @brief: получить значение ширины импульса Z в режиме ABZ
 * @return:
 *  MT6701I2_Z_PULSE_WIDTH_1LSB(Attention! Inverse rotation because the AS5600 measure on bottom side)
 *  MT6701I2_Z_PULSE_WIDTH_2LSB
 *  MT6701I2_Z_PULSE_WIDTH_4LSB
 *  MT6701I2_Z_PULSE_WIDTH_8LSB
 *  MT6701I2_Z_PULSE_WIDTH_12LSB
 *  MT6701I2_Z_PULSE_WIDTH_16LSB
 *  MT6701I2_Z_PULSE_WIDTH_180DEG
 *  MT6701I2_Z_PULSE_WIDTH_1LSB_2
 */
MT6701I2CZPulseWidth MT6701I2C::getZPulseWidth(void) {
  return (MT6701I2CZPulseWidth)((MT_RequestSingleRegister(MT6701_I2C_EEPROM_Z_PULSE_WIDTH_REG) >> MT6701_I2C_EEPROM_Z_PULSE_WIDTH_BIT_S) & 0x07); // 0x07 = 0b00000111
}
/*
 * @brief: установить ширину импульса Z 1LSB
 */
void MT6701I2C::setZPulseWidth1LSB(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_Z_PULSE_WIDTH_REG);
  bkup |= MT6701I2_Z_PULSE_WIDTH_1LSB << MT6701_I2C_EEPROM_Z_PULSE_WIDTH_BIT_S;
  MT_WriteOneByte(MT6701_I2C_EEPROM_Z_PULSE_WIDTH_REG, bkup);
}
/*
 * @brief: установить ширину импульса Z 1LSB с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setZPulseWidth1LSBVerify(void) {
  setZPulseWidth1LSB();
  return getZPulseWidth() == MT6701I2_Z_PULSE_WIDTH_1LSB ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/*
 * @brief: установить ширину импульса Z 2LSB
 */
void MT6701I2C::setZPulseWidth2LSB(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_Z_PULSE_WIDTH_REG);
  bkup |= MT6701I2_Z_PULSE_WIDTH_2LSB << MT6701_I2C_EEPROM_Z_PULSE_WIDTH_BIT_S;
  MT_WriteOneByte(MT6701_I2C_EEPROM_Z_PULSE_WIDTH_REG, bkup);
}
/*
 * @brief: установить ширину импульса Z 2LSB с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setZPulseWidth2LSBVerify(void) {
  setZPulseWidth2LSB();
  return getZPulseWidth() == MT6701I2_Z_PULSE_WIDTH_2LSB ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/*
 * @brief: установить ширину импульса Z 4LSB
 */
void MT6701I2C::setZPulseWidth4LSB(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_Z_PULSE_WIDTH_REG);
  bkup |= MT6701I2_Z_PULSE_WIDTH_4LSB << MT6701_I2C_EEPROM_Z_PULSE_WIDTH_BIT_S;
  MT_WriteOneByte(MT6701_I2C_EEPROM_Z_PULSE_WIDTH_REG, bkup);
}
/*
 * @brief: установить ширину импульса Z 4LSB с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setZPulseWidth4LSBVerify(void) {
  setZPulseWidth1LSB();
  return getZPulseWidth() == MT6701I2_Z_PULSE_WIDTH_4LSB ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/*
 * @brief: установить ширину импульса Z 8LSB
 */
void MT6701I2C::setZPulseWidth8LSB(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_Z_PULSE_WIDTH_REG);
  bkup |= MT6701I2_Z_PULSE_WIDTH_8LSB << MT6701_I2C_EEPROM_Z_PULSE_WIDTH_BIT_S;
  MT_WriteOneByte(MT6701_I2C_EEPROM_Z_PULSE_WIDTH_REG, bkup);
}
/*
 * @brief: установить ширину импульса Z 8LSB с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setZPulseWidth8LSBVerify(void) {
  setZPulseWidth8LSB();
  return getZPulseWidth() == MT6701I2_Z_PULSE_WIDTH_8LSB ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/*
 * @brief: установить ширину импульса Z 12LSB
 */
void MT6701I2C::setZPulseWidth12LSB(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_Z_PULSE_WIDTH_REG);
  bkup |= MT6701I2_Z_PULSE_WIDTH_12LSB << MT6701_I2C_EEPROM_Z_PULSE_WIDTH_BIT_S;
  MT_WriteOneByte(MT6701_I2C_EEPROM_Z_PULSE_WIDTH_REG, bkup);
}
/*
 * @brief: установить ширину импульса Z 12LSB с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setZPulseWidth12LSBVerify(void) {
  setZPulseWidth12LSB();
  return getZPulseWidth() == MT6701I2_Z_PULSE_WIDTH_12LSB ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/*
 * @brief: установить ширину импульса Z 16LSB
 */
void MT6701I2C::setZPulseWidth16LSB(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_Z_PULSE_WIDTH_REG);
  bkup |= MT6701I2_Z_PULSE_WIDTH_16LSB << MT6701_I2C_EEPROM_Z_PULSE_WIDTH_BIT_S;
  MT_WriteOneByte(MT6701_I2C_EEPROM_Z_PULSE_WIDTH_REG, bkup);
}
/*
 * @brief: установить ширину импульса Z 16LSB с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setZPulseWidth16LSBVerify(void) {
  setZPulseWidth16LSB();
  return getZPulseWidth() == MT6701I2_Z_PULSE_WIDTH_16LSB ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/*
 * @brief: установить ширину импульса Z 180 градусов
 */
void MT6701I2C::setZPulseWidth180DEG(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_Z_PULSE_WIDTH_REG);
  bkup |= MT6701I2_Z_PULSE_WIDTH_180DEG << MT6701_I2C_EEPROM_Z_PULSE_WIDTH_BIT_S;
  MT_WriteOneByte(MT6701_I2C_EEPROM_Z_PULSE_WIDTH_REG, bkup);
}
/*
 * @brief: установить ширину импульса Z 180 градусов с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setZPulseWidth180DEGVerify(void) {
  setZPulseWidth180DEG();
  return getZPulseWidth() == MT6701I2_Z_PULSE_WIDTH_180DEG ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/* 
 * @brief: получить значение нулевого положения
 * @note: СМОТРЕТЬ ТАБЛИЦУ В ДОКУМЕНТАЦИИ
 * @return:
 *  0 - 4095
 */
word MT6701I2C::getZeroDegreePositionData(void) {
  uint8_t reg_h = MT_RequestSingleRegister(MT6701_I2C_EEPROM_ZERO_REG_H) & 0x0F; // 0x0F = 0b00001111
  return (word)((reg_h << 8) | MT_RequestSingleRegister(MT6701_I2C_EEPROM_ZERO_REG_L));
}
/* 
 * @brief: установить значение нулевого положения
 * @note: СМОТРЕТЬ ТАБЛИЦУ В ДОКУМЕНТАЦИИ
 * @param _zero_position_data:
 *  0 - 4095
 */
void MT6701I2C::setZeroDegreePositionData(word _zero_position_data) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_ZERO_REG_H) & 0xF0; // 0xF0 = 0b11110000
  uint8_t reg_l = _zero_position_data & 0xFF;
  bkup |= _zero_position_data >> 8;
  MT_WriteOneByte(MT6701_I2C_EEPROM_ZERO_REG_H, bkup);
  MT_WriteOneByte(MT6701_I2C_EEPROM_ZERO_REG_L, reg_l);
}
/* 
 * @brief: установить значение нулевого положения с проверкой
 * @note: СМОТРЕТЬ ТАБЛИЦУ В ДОКУМЕНТАЦИИ
 * @param _zero_position_data:
 *  0 - 4095
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setZeroDegreePositionDataVerify(word _zero_position_data) {
  setZeroDegreePositionData(_zero_position_data);
  return getZeroDegreePositionData() == _zero_position_data ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/* 
 * @brief: получить значение частоты ШИМ
 * @return:
 *  MT6701I2_PWM_FREQUENCY_9944
 *  MT6701I2_PWM_FREQUENCY_4972
 */
MT6701I2CFrequencyPWM MT6701I2C::getFrequencyPWM(void) {
  return (MT6701I2CFrequencyPWM)((MT_RequestSingleRegister(MT6701_I2C_EEPROM_PWM_FREQ_REG) >> MT6701_I2C_EEPROM_PWM_FREQ_BIT) & 0x01);
}
/* 
 * @brief: установить значение частоты ШИМ 994.4Гц
 */
void MT6701I2C::setFrequencyPWM9944(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_PWM_FREQ_REG);
  bkup &= ~(1 << MT6701_I2C_EEPROM_PWM_FREQ_BIT);
  MT_WriteOneByte(MT6701_I2C_EEPROM_PWM_FREQ_REG, bkup);
}
/* 
 * @brief: установить значение частоты ШИМ 994.4Гц с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setFrequencyPWM9944Verify(void) {
  setFrequencyPWM9944();
  return getFrequencyPWM() == MT6701I2_PWM_FREQUENCY_9944 ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/* 
 * @brief: установить значение частоты ШИМ 497.2Гц
 */
void MT6701I2C::setFrequencyPWM4972(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_PWM_FREQ_REG);
  bkup |= 1 << MT6701_I2C_EEPROM_PWM_FREQ_BIT;
  MT_WriteOneByte(MT6701_I2C_EEPROM_PWM_FREQ_REG, bkup);
}
/* 
 * @brief: установить значение частоты ШИМ 497.2Гц с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setFrequencyPWM4972Verify(void) {
  setFrequencyPWM4972();
  return getFrequencyPWM() == MT6701I2_PWM_FREQUENCY_4972 ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/* 
 * @brief: получить значение полярности ШИМ
 * @return:
 *  MT6701I2_PWM_POLARITY_HIGH
 *  MT6701I2_PWM_POLARITY_LOW
 */
MT6701I2CPolarityPWM MT6701I2C::getPolarityPWM(void) {
  return (MT6701I2CPolarityPWM)((MT_RequestSingleRegister(MT6701_I2C_EEPROM_PWM_POL_REG) >> MT6701_I2C_EEPROM_PWM_POL_BIT) & 0x01);
}
/* 
 * @brief: установить значение полярности ШИМ HIGH
 */
void MT6701I2C::setPolarityPWMHigh(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_PWM_POL_REG);
  bkup &= ~(1 << MT6701_I2C_EEPROM_PWM_POL_BIT);
  MT_WriteOneByte(MT6701_I2C_EEPROM_PWM_POL_REG, bkup);
}
/* 
 * @brief: установить значение полярности ШИМ HIGH с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setPolarityPWMHighVerify(void) {
  setPolarityPWMHigh();
  return getPolarityPWM() == MT6701I2_PWM_POLARITY_HIGH ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/* 
 * @brief: установить значение полярности ШИМ LOW
 */
void MT6701I2C::setPolarityPWMLow(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_PWM_POL_REG);
  bkup |= 1 << MT6701_I2C_EEPROM_PWM_POL_BIT;
  MT_WriteOneByte(MT6701_I2C_EEPROM_PWM_POL_REG, bkup);
}
/* 
 * @brief: установить значение полярности ШИМ LOW с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setPolarityPWMLowVerify(void) {
  setPolarityPWMLow();
  return getPolarityPWM() == MT6701I2_PWM_POLARITY_LOW ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}

/* 
 * @brief: получить режима выхода
 * @return:
 *  MT6701I2_OUTPUT_MODE_ANALOG
 *  MT6701I2_OUTPUT_MODE_PWM
 */
MT6701I2COutputMode MT6701I2C::getOutputMode(void) {
  return (MT6701I2COutputMode)((MT_RequestSingleRegister(MT6701_I2C_EEPROM_OUT_MODE_REG) >> MT6701_I2C_EEPROM_OUT_MODE_BIT) & 0x01);
}
/* 
 * @brief: установить режим выхода Аналог
 */
void MT6701I2C::setOutputModeAnalog(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_OUT_MODE_REG);
  bkup &= ~(1 << MT6701_I2C_EEPROM_OUT_MODE_BIT);
  MT_WriteOneByte(MT6701_I2C_EEPROM_OUT_MODE_REG, bkup);
}
/* 
 * @brief: установить режим выхода Аналог с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setOutputModeAnalogVerify(void) {
  setOutputModeAnalog();
  return getOutputMode() == MT6701I2_OUTPUT_MODE_ANALOG ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
/* 
 * @brief: установить режим выхода ШИМ
 */
void MT6701I2C::setOutputModePWM(void) {
  uint8_t bkup = MT_RequestSingleRegister(MT6701_I2C_EEPROM_OUT_MODE_REG);
  bkup |= 1 << MT6701_I2C_EEPROM_OUT_MODE_BIT;
  MT_WriteOneByte(MT6701_I2C_EEPROM_OUT_MODE_REG, bkup);
}
/* 
 * @brief: установить режим выхода ШИМ с проверкой
 * @return:
 *  MT6701I2C_DEFAULT_REPORT_ERROR - не установлено
 *  MT6701I2C_DEFAULT_REPORT_OK - установлено
 */
bool MT6701I2C::setOutputModePWMVerify(void) {
  setOutputModePWM();
  return getOutputMode() == MT6701I2_OUTPUT_MODE_PWM ? MT6701I2C_DEFAULT_REPORT_OK : MT6701I2C_DEFAULT_REPORT_ERROR;
}
