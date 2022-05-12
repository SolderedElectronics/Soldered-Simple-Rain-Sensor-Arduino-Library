/**
 **************************************************

    @file        Read_values_easyC.ino
    @brief       Example for using the digital and analog read functions for Simple rain with easyC


 	product: www.solde.red/333043

    @authors     Goran Juric for Soldered.com
 ***************************************************/

#include "Simple-rain-sensor-easyC-SOLDERED.h"

#define CALIBRATION_VALUE_ON_DRY 1023

// Declare the sensor object
SimpleRainSensor sensor;

void setup()
{
    // Initialize the serial communication via UART
    Serial.begin(115200);

    // Initialize the sensor
    sensor.begin();

    //Sensor will work just fine if it is not calibrated
    //but since it is relying on resistance of water and
    //and water significantly changes resistance if it is
    //filled with particles, it smart idea to calibrate sometimes.
    //For calibration it is needed to measure output value of sensor
    //sensor is placed on wanted place  and when it is full dry
    //First program Dasduino using this sketch and read value from sensor
    //and write that value in CALIBRATION_VALUE_ON_DRY
    sensor.calibrate(CALIBRATION_VALUE_ON_DRY);

}

void loop()
{
    Serial.print("Raw value of sensor: "); // Print information message
    Serial.println(sensor.getValue());  // Prints percent value of rain sensor

    Serial.print("Resistance of sensor: "); // Print information message
    Serial.print(sensor.getResistance());  // Prints resistance of rain sensor
    Serial.println(" Ohms.");              // Print information message

    if(sensor.isRaining())
    {
        Serial.println("Rain is detected");
    }
    else
    {
        Serial.println("Rain is not detected");
    }

    delay(1000);
}
