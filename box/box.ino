#include <cstring>
#include <Arduino.h>

#include "definitions.hpp"
#include "GPSmodule.hpp"

// use the mcu as a serial converter
//#define PASSTHROUGH

GPSmodule gps = NULL;

void setup()
{
    Serial.begin(9600);
    LOG("Starting");
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
    LOG("Starting GPSmodule");
    gps = GPSmodule(&Serial2);
}

void loop()
{
    delay(300);
    gps.process();
    gps.print();
}