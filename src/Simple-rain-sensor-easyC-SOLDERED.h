/**
 **************************************************
 *
 * @file        Simple-rain-humidity-sensor-easyC-SOLDERED.h
 * @brief       Header file for sensor specific code.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Goran Juric @ soldered.com
 ***************************************************/

#ifndef _SIMPLE_RAIN_SENSOR_EASYC_
#define _SIMPLE_RAIN_SENSOR_EASYC_

#include "Arduino.h"
#include "libs/Generic-easyC/easyC.hpp"
#include "math.h"

class SimpleRainSensor : public EasyC
{
  public:
    SimpleRainSensor();
    SimpleRainSensor(int);
    uint32_t getValue(void);
    float getResistance(void);
    void calibrate(int);
    void setADCWidth(uint8_t);
    bool isRaining();
    void setThreshold(byte);

  protected:
    void initializeNative();

  private:
    float a, b, high = 1023;
    int pin;
    uint16_t ADC_width = 1023;
    byte data[2], threshold;
    uint16_t resistance;
};

#endif
