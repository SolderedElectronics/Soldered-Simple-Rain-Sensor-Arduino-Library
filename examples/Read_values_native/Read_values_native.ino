/**
 **************************************************

    @file        Read_values_native.ino
    @brief       Example for using the digital and analog read functions for Simple rain sensor


    product: www.solde.red/333044

    @authors     Goran Juric for Soldered.com
 ***************************************************/

#include "Simple-rain-sensor-easyC-SOLDERED.h"

//Connecting diagram
//Breakout      Arduino

//|-------------|
//D0------------9
//A0------------A0
//GND-----------GND
//VCC-----------5V

#define ANALOG_PIN A0
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
    pinMode(DIGITAL_PIN, INPUT);
}

void loop()
{
    Serial.print("Raw value of sensor: "); // Print information message
    Serial.println(sensor.getValue());  // Prints percent value of rain sensor

    Serial.print("Resistance of sensor: "); // Print information message
    Serial.print(sensor.getResistance());  // Prints resistance of rain sensor
    Serial.println(" Ohms.");              // Print information message

    if(digitalRead(9))
    {
        Serial.println("Rain is not detected");
    }
    else
    {
        Serial.println("Rain is detected");
    }

    delay(1000);
}
