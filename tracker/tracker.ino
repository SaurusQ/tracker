#include <cstring>
#include <Arduino.h>

#include "definitions.hpp"
#include "pinConfiguration.hpp"

#include "GPSmodule.hpp"
#include "LiquidCrystal_I2C.hpp"
#include "bluetooth.hpp"

GPSmodule gps = GPSmodule(&Serial2);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(LCD_ADDR, 16, 2, LCD_SDA, LCD_SCL);
Bluetooth blue = Bluetooth();

void setup()
{
    Serial.begin(9600);
    LOG("Starting");
    Serial2.begin(9600);
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

void loop()
{
    LOG("Loop");
    for(int i = 0; i < 50; i++) gps.process();
    blue.process();
    lcd.clear();
    lcd.home();
    lcd.print("lat:");
    lcd.print(gps.getDegLatFloat());
    lcd.setCursor(0, 1);
    lcd.print("lon:");
    lcd.print(gps.getDegLonFloat());
    delay(1000);
}