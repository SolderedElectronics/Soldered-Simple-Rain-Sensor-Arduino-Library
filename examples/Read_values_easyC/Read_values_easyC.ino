/**
 **************************************************

    @file        Read_values_easyC.ino
    @brief       Example for using the digital and analog read functions for Simple rain with easyC

                 For this example, you will need any Dasduino board, a USB-c cable, a Simple rain sensor with easyC, and easyC cable. 
                 Don't have Dasduino? Get it here: https://soldered.com/categories/dasduino-arduino/dasduino-boards/ 
                 Don't have easyC cable? Get it here: https://soldered.com/categories/easyc-2/easyc-cables-adapters/

                 This example will show you how to calibrate the sensor, set the threshold for 
                 turning on the LED and detecting the rain. Open the Serial Monitor at 115200 baud rate to see what's happening.

    product: www.solde.red/333043

    @authors     Goran Juric, Karlo Leksic for Soldered.com
 ***************************************************/

// Include Soldered library for Simple sensor
// If you don't have a library, get it here: https://github.com/SolderedElectronics/Soldered-Simple-Rain-Sensor-Arduino-Library
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
    // and write that value in CALIBRATION_VALUE_ON_DRY
    sensor.calibrate(CALIBRATION_VALUE_ON_DRY);

    // Set threshold for LED on the breakout
    sensor.setRawThreshold(250); // or
    // sensor.setThreshold(25.1); // 25.1%
}

void loop()
{
    Serial.print("Value of sensor: "); // Print information message
    Serial.print(sensor.getValue());   // Prints percent value of rain sensor
    Serial.print("% ");
    Serial.println(sensor.getRawValue()); // Prints raw value of rain sensor

    Serial.print("Resistance of sensor: "); // Print information message
    Serial.print(sensor.getResistance());   // Prints resistance of rain sensor
    Serial.println(" Ohms.");               // Print information message

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
    delay(200);
}
