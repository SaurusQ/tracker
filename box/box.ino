#include <cstring>
#include <Arduino.h>

#include "definitions.hpp"
#include "GPSreader.hpp"

// use the mcu as a serial converter
#define PASSTHROUGH

GPSreader gps = NULL;

void setup()
{
    Serial.begin(9600);
    Serial.print("Starting");
    Serial2.begin(9600);
    #ifdef PASSTHROUGH
    while(true)
    {
        if(Serial.available())
            Serial2.write(Serial.read());
        if(Serial2.available())
            Serial.write(Serial2.read());
    }
    #endif
    gps = GPSreader(&Serial2);
}

void loop()
{
    UBXmsg* msg = gps.process();
    if(msg != nullptr)
    {
        Serial.println(msg->toString());
    }
}