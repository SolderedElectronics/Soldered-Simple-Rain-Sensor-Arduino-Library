/**
 **************************************************
 *
 * @file        Simple-soil-sensor-easyC-SOLDERED.cpp
 * @brief       Example functions to overload in base class.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Goran Juric, Karlo Leksic @ soldered.com
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
 * @brief       Function for reading value of soil sensor in percent
 *
 * @return      Value of soil sensor in percent (0 - 100)
 */
float SimpleRainSensor::getValue()
{
    return (getRawValue() / float(1023) * 100);
}

/**
 * @brief       Function for reading raw value of soil sensor (0 - 1023)
 *
 * @return      Raw value of soil sensor (0 - 1023)
 */
uint16_t SimpleRainSensor::getRawValue()
{
    if (!native)
    {
        // Read 2 bytes of raw  data
        char data[2];
        readData(data, 2);

        // Convert it to uint16_t
        resistance = *(uint16_t *)data;

        // Return converted value
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
    uint16_t temp = getRawValue();
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
    if (getRawValue() < high * 0.95)
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
 * @param       float _threshold value in %
 */
void SimpleRainSensor::setThreshold(float _threshold)
{
    // Check if the threshold is the proper value
    if (_threshold < 0 || _threshold > 100)
    {
        return;
    }

    // Convert percentage threshold to raw value and send it
    uint16_t rawThreshold = _threshold * 0.01 * 1024;
    setRawThreshold(rawThreshold);
}

/**
 * @brief       Get threshold value that was prevously set
 *
 * @returns     float of the threshold
 */
float SimpleRainSensor::getThreshold()
{
    return threshold;
}


/**
 * @brief       Function to set raw threshold value to turn on the LED
 *
 * @param       uint16_t _threshold from 0 to 1023 (raw)
 */
void SimpleRainSensor::setRawThreshold(uint16_t _threshold)
{
    // Check if the threshold is the proper value
    if (_threshold < 0 || _threshold > 1023)
    {
        return;
    }

    // Convert raw threshold value into 2 bytes for sending
    uint8_t *rawThreshold = (uint8_t *)&_threshold;

    // Send raw threshold
    sendData(rawThreshold, 2);
}

/**
 * @brief       Invert the LED on the breakout board
 *
 * @param       bool ledSetting:
 *              -True makes the LED turn off when the threshold is reached
 *              -False will have the LED turn on only when the threshold is reached
 */
void SimpleRainSensor::invertLED(bool ledSetting)
{
    if (ledSetting)
    {
        const uint8_t dataToSend[1] = {LED_OFF_WHEN_THRESHOLD};
        sendData(dataToSend, 1);
    }
    else
    {
        const uint8_t dataToSend[1] = {LED_ON_WHEN_THRESHOLD};
        sendData(dataToSend, 1);
    }
}