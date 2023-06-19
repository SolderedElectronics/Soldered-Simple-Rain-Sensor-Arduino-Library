/**
 **************************************************
 *
 * @file        Simple-rain-humidity-sensor-easyC-SOLDERED.h
 * @brief       Header file for the Simple Rain Sensor by Soldered
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

// Settings for the LED which
#define LED_ON_WHEN_THRESHOLD  0xFF
#define LED_OFF_WHEN_THRESHOLD 0x00

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
    float getThreshold();
    void setRawThreshold(uint16_t);
    void invertLED(bool);

  protected:
    void initializeNative();

  private:
    float a, b, high = 1023;
    int pin;
    uint16_t ADC_width = 1023;
    byte data[2];
    float threshold = 0.9;
    uint16_t resistance;
};

#endif
