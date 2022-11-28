/**
 **************************************************
 *
 * @file        Simple-soil-sensor-easyC-SOLDERED.cpp
 * @brief       Example functions to overload in base class.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Goran Juric @ soldered.com
 ***************************************************/


#include "Simple-rain-sensor-easyC-SOLDERED.h"

/**
 * @brief                   Default constructor.
 *
 */
SimpleRainSensor::SimpleRainSensor()
{
}

/**
 * @brief                   Sensor specific native constructor.
 *
 * @param int _pin          Pin on which is sensor connected.
 */
SimpleRainSensor::SimpleRainSensor(int _pin)
{
    pin = _pin;
    native = 1;
}

/**
 * @brief                   Overloaded function for virtual in base class to initialize sensor specific.
 */
void SimpleRainSensor::initializeNative()
{
}

/**
 * @brief       Function for reading value of soil sensor
 *
 * @return      value of soil sensor
 */
uint32_t SimpleRainSensor::getValue()
{
    if (!native)
    {
        Wire.beginTransmission(address);
        Wire.requestFrom(address, 2);

        if (Wire.available())
        {
            Wire.readBytes(data, 2);
        }
        Wire.endTransmission();

        resistance = *(uint16_t *)data;
        return resistance;
    }
    return analogRead(pin);
}

/**
 * @brief       Function for calculating resistance of soil sensor
 *
 * @return      resistance of soil sensor
 */
float SimpleRainSensor::getResistance()
{
    uint16_t temp = getValue();
    if (temp != 0)
    {
        return 10000 * (temp / (float)(ADC_width - temp));
    }
    return 0;
}

/**
 * @brief       Function for calibrating sensor
 *
 * @param _high Calibration value for sensor in air
 */
void SimpleRainSensor::calibrate(int _high)
{
    high = _high;
}

/**
 * @brief       Function for setting ADC bit width of microcontroller
 *
 * @param       uint8_t _ADC_width ADC bit width in bits
 */
void SimpleRainSensor::setADCWidth(uint8_t _ADC_width)
{
    ADC_width = pow(2, _ADC_width) - 1;
}

/**
 * @brief       Function for looking if it's raining
 *
 * @return      1 if it is raining, 0 if not
 */
bool SimpleRainSensor::isRaining()
{
    if (getResistance() < high * 0.95)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief       Function to set threshold value to turn on the LED
 * 
 * @param       byte _threshold value in %
*/
void SimpleRainSensor::setThreshold(byte _threshold)
{
    if(_threshold > 100)
    {
        return;
    }
    threshold = _threshold;
    Wire.beginTransmission(address);
    Wire.write(threshold);
    Wire.endTransmission();
}