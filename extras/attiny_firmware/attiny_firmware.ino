/**
 **************************************************

   @file        attiny_firmware for Simple fire
                sensor with easyC
   @brief       This sensor sends light intensity
                measured with IR light sensor on breakout board



   @authors     Goran Juric, Karlo Leksic for Soldered.com
 ***************************************************/

#include "easyC.h"
#include <Wire.h>

int addr = DEFAULT_ADDRESS; // 0x30

volatile uint16_t readValue; // Variable for reading an analog value
byte threshold;              // Variable for setting the threshold

// Define pins for the sensor and LED
#define LED_PIN    PA4
#define SENSOR_PIN PA5

void setup()
{
    // Set address switches as inputs, and get the I2C address
    initDefault();
    addr = getI2CAddress();

    // Init I2C communication
    Wire.begin(addr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);

    // Set the LED pin as output and turn it on
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
}

void loop()
{
    // Read analog value
    readValue = analogRead(SENSOR_PIN);

    // Turn on the LED if the read value is greater than the threshold value
    if (readValue > (threshold * 0.01 * 1024))
    {
        digitalWrite(LED_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
    }

    // Delay between readings
    delay(20);
}

// This function will be executed when Dasduino sends data to the breakout
void receiveEvent(int howMany)
{
    // The breakout only receives a threshold value so read it and store
    if (Wire.available())
    {
        threshold = Wire.read();
    }
}

// This function will be executed when Dasduino requests data from the breakout
void requestEvent()
{
    // Here is needed to convert the read value into bytes appropriate for sending
    byte *valueForSend = (byte *)&readValue; // One uint16_t converted to 2 uint8_t
    Wire.write(valueForSend, 2);             // Send 2 uint8_t (bytes)
}