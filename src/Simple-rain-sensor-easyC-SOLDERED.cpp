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
        readRegister(ANALOG_READ_REG, raw, 2 * sizeof(uint8_t));
        return raw[0] | (raw[1]) << 8;
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
 *
 * @param _low Calibration value for sensor fully in water
 *
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
 * @brief       Function for setting ADC bit width of microcontroller
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