
#include <Arduino.h>

void setup()
{
    Serial.begin(9600);
    Serial2.begin(9600);
}

void loop()
{
    if(Serial.available())
    {
        uint8_t byte = Serial.read();
        Serial2.write(byte);
        //Serial1.print(byte, HEX);
    }

    if(Serial2.available())
    {
        uint8_t byte = Serial2.read();
        Serial.write(byte);
    }
}
