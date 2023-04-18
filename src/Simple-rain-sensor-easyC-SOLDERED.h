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
    float getValue(void);
    uint16_t getRawValue(void);
    float getResistance(void);
    void calibrate(int);
    void setADCWidth(uint8_t);
    bool isRaining();
    void setThreshold(float);
    void setRawThreshold(uint16_t);

  protected:
    void initializeNative();

  private:
    float a, b, high = 1023;
    int pin;
    uint16_t ADC_width = 1023;
    byte data[2];
    float threshold;
    uint16_t resistance;
};

#endif
