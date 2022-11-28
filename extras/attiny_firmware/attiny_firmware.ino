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

int addr = DEFAULT_ADDRESS;

volatile uint16_t readValue;
byte threshold;

void setup()
{
    initDefault();
    addr = getI2CAddress();

    Wire.begin(addr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
    pinMode(PA4, OUTPUT);
    digitalWrite(PA4, HIGH);

    Serial.begin(115200);
}

void loop()
{
    readValue = analogRead(PA5);
    if (readValue > (threshold * 0.01 * 1024))
    {
        digitalWrite(PA4, HIGH);
    }
    else
    {
        digitalWrite(PA4, LOW);
    }
    delay(20);
}

void receiveEvent(int howMany)
{
    if (Wire.available())
    {
        threshold = Wire.read();
    }
}

void requestEvent()
{
    byte *valueForSend = (byte *)&readValue;
    Wire.write(valueForSend, 2);
}