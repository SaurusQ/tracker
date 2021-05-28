#include <cstring>
#include <Arduino.h>

#include "definitions.hpp"
#include "pinConfiguration.hpp"

#include "GPSmodule.hpp"
#include "LiquidCrystal_I2C.hpp"

// use the mcu as a serial converter
//#define PASSTHROUGH

GPSmodule gps = NULL;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(LCD_ADDR, 16, 2, LCD_SDA, LCD_SCL);

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
    LOG("Initializing lcd");
    lcd.init();
    lcd.backlight();
    lcd.print("Tracker TM");
    delay(2000);
}

void loop()
{
    LOG("Loop");
    gps.process();
    delay(1000);
    lcd.clear();
    lcd.home();
    lcd.print("lat:");
    lcd.print(gps.getDeg().lat);
    lcd.setCursor(0, 1);
    lcd.print("lon:");
    lcd.print(gps.getDeg().lon);
}