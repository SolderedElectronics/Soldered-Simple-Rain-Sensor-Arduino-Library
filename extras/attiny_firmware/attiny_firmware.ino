/**
 **************************************************
 *
 * @file        attiny_firmware for Simple rain sensor 
 *              sensor with easyC
 * @brief       This sensor sends rain intensity
 *              measured with resistive water senosr 
 *              on breakout board
 *
 *
 *
 * @authors     Goran Juric for Soldered.com
 ***************************************************/

#include "easyC.h"
#include <Wire.h>

int addr = DEFAULT_ADDRESS;

void setup()
{
    initDefault();
    addr = getI2CAddress();

    Wire.begin(addr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
    pinMode(PA4,OUTPUT);
    digitalWrite(PA4,HIGH);
}

void loop()
{
}

char lastEvent;

void receiveEvent(int howMany)
{
    while (1 < Wire.available())
    {
        char c = Wire.read();
    }

    lastEvent = Wire.read();
}

void requestEvent()
{
    int c = 0;
    char a[2];
    if (lastEvent==0)
    {
      c = analogRead(PA5);
      a[1] = c >> 8;
      a[0] = c & 0xFF;
      Wire.write(a, 2);
    }
}
