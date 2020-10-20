/*!
 *  @file Adafruit_EMC2101.h
 *
 * 	I2C Driver for the Adafruit EMC2101 Temperature monitor and fan
 *controller This is a library is written to work with the Adafruit EMC2101
 *breakout: https://www.adafruit.com/products/47nn
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *
 *	BSD license (see license.txt)
 */
// "requires_busio": "y",
//   "requires_sensor": "y",
#ifndef _ADAFRUIT_EMC2101_H
#define _ADAFRUIT_EMC2101_H

#include "Arduino.h"
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>

#include <Wire.h>
#define EMC2101_I2CADDR_DEFAULT 0x4C ///< EMC2101 default i2c address
#define EMC2101_CHIP_ID 0x16         ///< EMC2101 default device id from part id
#define EMC2101_ALT_CHIP_ID 0x28 ///< EMC2101 alternate device id from part id
#define EMC2101_WHOAMI 0xFD      ///< Chip ID register

#define EMC2101_INTERNAL_TEMP 0x00
#define EMC2101_EXTERNAL_TEMP_MSB 0x01
#define EMC2101_EXTERNAL_TEMP_LSB 0x10

#define EMC2101_STATUS 0x02
#define EMC2101_REG_CONFIG 0x03
#define EMC2101_REG_DATA_RATE 0x04
#define EMC2101_TEMP_FORCE 0x0C
#define EMC2101_TACH_LSB 0x46
#define EMC2101_TACH_MSB 0x47
#define EMC2101_TACH_LIMIT_LSB 0x48
#define EMC2101_TACH_LIMIT_MSB 0x49
#define EMC2101_FAN_CONFIG 0x4A
#define EMC2101_FAN_SPINUP 0x4B
#define EMC2101_REG_FAN_SETTING 0x4C
#define EMC2101_LUT_HYSTERESIS 0x4F

#define EMC2101_TEMP_FILTER 0xBF
#define EMC2101_REG_PARTID 0xFD // 0x16
#define EMC2101_REG_MFGID 0xFE  // 0xFF16

#define MAX_LUT_SPEED 0x3F // 6-bit value
#define MAX_LUT_TEMP 0x7F  //  7-bit

#define EMC2101_I2C_ADDR 0x4C
#define EMC2101_FAN_RPM_DIVISOR 5400000
#define _TEMP_LSB 0.125

#define MAX_LUT_SPEED 0x3F ///< 6-bit value
#define MAX_LUT_TEMP 0x7F  ///< 7-bit
///////////////////////////////////////////////////////////////
/**
 * @brief
 *
 * Allowed values for `setDataRate`.
 */
typedef enum {
  EMC2101_RATE_1_16_HZ, ///< 1_16_HZ
  EMC2101_RATE_1_8_HZ,  ///< 1_8_HZ
  EMC2101_RATE_1_4_HZ,  ///< 1_4_HZ
  EMC2101_RATE_1_2_HZ,  ///< 1_2_HZ
  EMC2101_RATE_1_HZ,    ///< 1_HZ
  EMC2101_RATE_2_HZ,    ///< 2_HZ
  EMC2101_RATE_4_HZ,    ///< 4_HZ
  EMC2101_RATE_8_HZ,    ///< 8_HZ
  EMC2101_RATE_16_HZ,   ///< 16_HZ
  EMC2101_RATE_32_HZ,   ///< 32_HZ
} emc2101_rate_t;

/*!
 *    @brief  Class that stores state and functions for interacting with
 *            the EMC2101 Temperature monitor and fan controller
 */
class Adafruit_EMC2101 {
public:
  Adafruit_EMC2101();
  ~Adafruit_EMC2101();

  bool begin(uint8_t i2c_addr = EMC2101_I2CADDR_DEFAULT, TwoWire *wire = &Wire);

  void reset(void);
  float getExternalTemperature(void);
  int8_t getInternalTemperature(void);
  uint16_t getFanRPM(void);
  float getDutyCycle(void);
  void setDutyCycle(float pwm_duty_cycle);

  uint16_t getFanMaxRPM(void);
  void setFanMaxRPM(float uint16_t);

  emc2101_rate_t getDataRate(void);
  bool setDataRate(emc2101_rate_t data_rate);

  bool LUTEnabled(void);
  bool LUTEnabled(bool enable_lut);

private:
  void _read(void);
  bool _init(void);

  Adafruit_I2CDevice *i2c_dev = NULL; ///< Pointer to I2C bus interface
};

#endif
