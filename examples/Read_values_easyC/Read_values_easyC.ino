/**
 **************************************************
 *
 * @file        Read_values_easyC.ino
 * @brief       Example for using the digital and analog read functions for Simple Rain Sensor with easyC.
 *              Also, see how to calibrate the sensor.
 *
 *              To successfully run the sketch:
 *              -Connect the breakout to your Dasduino board with easyC
 *              -Connect the rain sensor module to the breakout as well
 *              -Open serial monitor at 115200 baud!
 *
 *              Simple Rain Sensor with easyC: solde.red/333043
 *              Dasduino Core: www.solde.red/333037
 *              Dasduino Connect: www.solde.red/333034
 *              Dasduino ConnectPlus: www.solde.red/333033
 *
 * @authors     Goran Juric, Karlo Leksic @ soldered.com
 ***************************************************/

// Include Soldered library for Simple sensor
#include "Simple-rain-sensor-easyC-SOLDERED.h"

// Calibration value when the sensor is dry
#define CALIBRATION_VALUE_ON_DRY 1023

// Declare the sensor object
SimpleRainSensor sensor;

void setup()
{
    // Initialize the serial communication via UART
    Serial.begin(115200);

    // Initialize the sensor
    // Start I2C communication on default address (0x30)
    sensor.begin();

    // If you want another I2C address, enter it in the bracket
    // You can set another I2C address (0x31 - 0x37) by changing address switches on the breakout
    // NOTE: You have to restart breakout to apply the address change by unplugging and plugging
    // the easyC or USB-c from the Dasduino
    // sensor.begin(0x31);

    // Sensor will work just fine if it is not calibrated
    // but since it is relying on resistance of water and
    // and water significantly changes resistance if it is
    // filled with particles, it smart idea to calibrate sometimes.
    // For calibration it is needed to measure output value of sensor
    // sensor is placed on wanted place and when it is full dry
    // First program Dasduino using this sketch and read raw value from sensor
    // and write that value in the CALIBRATION_VALUE_ON_DRY variable
    sensor.calibrate(CALIBRATION_VALUE_ON_DRY);

    // Set threshold for LED on the breakout by raw value
    //sensor.setRawThreshold(250); // or percentage:
    sensor.setThreshold(98.1); // 25.1%

    // If you want the LED to turn OFF when the threshold is reached, use:
    sensor.invertLED(false);
}

void loop()
{
    Serial.print("Value of sensor: ");
    Serial.print(sensor.getValue()); // Prints percent value of rain sensor
    Serial.print("% ");
    Serial.println(sensor.getRawValue()); // Prints raw value of rain sensor

    Serial.print("Resistance of sensor: ");
    Serial.print(sensor.getResistance()); // Prints resistance of rain sensor
    Serial.println(" Ohms.");

    // Detect if it's raining or not
    // And print information accordingly
    if (sensor.isRaining())
    {
        Serial.println("Rain is detected");
    }
    else
    {
        Serial.println("Rain is not detected");
    }
    Serial.println();

    // Wait a bit before next reading
    delay(1000);
}
