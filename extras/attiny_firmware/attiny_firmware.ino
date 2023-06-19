/**
 **************************************************

   @file        attiny_firmware for Simple rain sensor with easyC

   @brief       This sensor measures resistance of the module which can detect rain


   @authors     Goran Juric, Karlo Leksic for Soldered.com
 ***************************************************/

#include "easyC.h"
#include <Wire.h>

int addr = DEFAULT_ADDRESS; // 0x30

volatile uint16_t readValue; // Variable for reading an analog value
uint16_t threshold;          // Variable for setting the threshold

// Define pins for the sensor and LED
#define LED_PIN    PA4
#define SENSOR_PIN PA5

// For setting the LED setting via I2C
bool ledInverted = false;
#define LED_ON_WHEN_THRESHOLD  0xFF
#define LED_OFF_WHEN_THRESHOLD 0x00

void setup()
{
    // Set address switches as inputs, and get the I2C address
    initDefault();
    addr = getI2CAddress();

    // Init I2C communication
    Wire.begin(addr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);

    // Set the LED pin as output and turn it off by default
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void loop()
{
    // Read analog value
    readValue = analogRead(SENSOR_PIN);

    // Turn on the LED if the read value is greater than the threshold value
    // If the led was inverted by the setting, invert it
    if (readValue > threshold)
    {
        digitalWrite(LED_PIN, (ledInverted) ? HIGH : LOW);
    }
    else
    {
        digitalWrite(LED_PIN, (ledInverted) ? LOW : HIGH);
    }

    // Delay between readings
    delay(20);
}

// This function will be executed when Dasduino sends data to the breakout
void receiveEvent(int howMany)
{
    // The breakout can recieve a threshold value or a 'Invert LED' setting

    // If two bytes are incoming, it's the threshold
    if (howMany == 2)
    {
        // Array for the raw data in bytes
        uint8_t recieved[2];

        // Read 2 bytes which represents the raw threshold value
        Wire.readBytes(recieved, 2);

        // Converts this value into uint16_t
        threshold = *(uint16_t *)recieved;
    }
    // If one byte is coming, it's the invert LED setting
    else if (howMany == 1)
    {
        uint8_t recieved [1];
        Wire.readBytes(recieved, 1);

        // Set the LED according to what was sent
        if (recieved[0] == LED_OFF_WHEN_THRESHOLD)
        {
            ledInverted = true;
        }
        else if(recieved[0] == LED_ON_WHEN_THRESHOLD)
        {
            ledInverted = false;
        }
    }
}

// This function will be executed when Dasduino requests data from the breakout
void requestEvent()
{
    // Here is needed to convert the read value into bytes appropriate for sending
    byte *valueForSend = (byte *)&readValue; // One uint16_t converted to 2 uint8_t
    Wire.write(valueForSend, 2);             // Send 2 uint8_t (bytes)
}