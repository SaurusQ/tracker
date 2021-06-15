#include <cstring>
#include <Arduino.h>

#include "definitions.hpp"
#include "pinConfiguration.hpp"

#include "GPSmodule.hpp"
#include "LiquidCrystal_I2C.hpp"
#include "bluetooth.hpp"
#include "GPShelper.hpp"

GPSmodule gps = GPSmodule(&Serial2);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(LCD_ADDR, 16, 2, LCD_SDA, LCD_SCL);
Bluetooth blue = Bluetooth();

void buttonInterrupt();
uint32_t buttonPresses = 0;
unsigned long lastPress = 0;

void setup()
{
    Serial.begin(9600);
    Serial2.begin(9600);
    LOG("Starting");
    attachInterrupt(BUTTON_PIN, buttonInterrupt, RISING);
    LOG("Init GPSmodule");
    gps.init();
    LOG("Init bluetooth");
    blue.init();
    LOG("Init lcd");
    lcd.init();
    lcd.backlight();
    lcd.print("Tracker TM");
    delay(2000);
}

void buttonInterrupt()
{
    unsigned long curPress = millis();
    if(lastPress - curPress > 200)
        buttonPresses++;
    lastPress = curPress;
}

void showMyCoord()
{
    lcd.print("lat:");
    lcd.print(gps.getDegLatFloat());
    lcd.print("LOC");
    lcd.setCursor(0, 1);
    lcd.print("lon:");
    lcd.print(gps.getDegLonFloat());
}

void showTargetCoord()
{
    lcd.print("lat:");
    lcd.print(blue.getLat());
    lcd.print("TAR");
    lcd.setCursor(0, 1);
    lcd.print("lon:");
    lcd.print(blue.getLon());
}

void showTrackingData()
{
    lcd.print("Distance: ");
    float dis = GPShelper::distaceBetweenCoordinates(51.5, 0, 38.8, -77.1);
    lcd.print(dis);
    lcd.setCursor(0, 1);
    lcd.print("Nice direction");
}

void loop()
{
    LOG("Loop");
    for(int i = 0; i < 50; i++) gps.process();
    blue.process();
    lcd.clear();
    lcd.home();

    switch(buttonPresses % 3)
    {
        case 0:
            showTrackingData();
            break;
        case 1:
            showMyCoord();
            break;
        case 2:
            showTargetCoord();
            break;
        default:
            LOG("WTF did you do");
            break;
    }
    delay(1000);
}