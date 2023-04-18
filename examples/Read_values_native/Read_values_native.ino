/**
 **************************************************

    @file        Read_values_native.ino
    @brief       Example for using the digital and analog read functions for Simple rain sensor.

                 For this example, you will need any Dasduino board, a USB-c cable, a Simple rain sensor with easyC, and easyC cable. 
                 Don't have Dasduino? Get it here: https://soldered.com/categories/dasduino-arduino/dasduino-boards/ 
                 Don't have easyC cable? Get it here: https://soldered.com/categories/easyc-2/easyc-cables-adapters/

                 This example will show you how to calibrate the sensor, set ADC word width, set the threshold for 
                 turning on the LED and detecting the rain. Open the Serial Monitor at 115200 baud rate to see what's happening.

    product: www.solde.red/333044

    @authors     Goran Juric for Soldered.com
 ***************************************************/

// Include Soldered library for Simple sensor
// If you don't have a library, get it here: https://github.com/SolderedElectronics/Soldered-Simple-Rain-Sensor-Arduino-Library
#include "Simple-rain-sensor-easyC-SOLDERED.h"

// Connecting diagram
// Breakout      Arduino

// |-------------|
// D0------------9
// A0------------A0
// GND-----------GND
// VCC-----------5V

// Define your pins
#define ANALOG_PIN  A0
#define DIGITAL_PIN 9

// Declare the sensor object and set pin on which sensor is connected
SimpleRainSensor sensor(ANALOG_PIN);

void setup()
{
    // Initialize the serial communication via UART
    Serial.begin(115200);

    // Initialize the sensor
    sensor.begin();

    // If different microcontroller with different bit width
    // is used, it should be set using this function
    sensor.setADCWidth(10);

    // You can use potentiometer on breakout board to set treshold
    // to sense rain.
    pinMode(DIGITAL_PIN, INPUT_PULLUP);
}

void loop()
{
    Serial.print("Raw value of sensor: "); // Print information message
    Serial.print(sensor.getValue());       // Prints percent value of rain sensor
    Serial.print("% ");
    Serial.println(sensor.getRawValue()); // Prints raw value of rain sensor

    Serial.print("Resistance of sensor: "); // Print information message
    Serial.print(sensor.getResistance());   // Prints resistance of rain sensor
    Serial.println(" Ohms.");               // Print information message

    if (digitalRead(DIGITAL_PIN))
    {
        Serial.println("Rain is not detected");
    }
    else
    {
        Serial.println("Rain is detected");
    }
    Serial.println();

    // Wait a bit before next reading
    delay(200);
}
