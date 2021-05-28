
#pragma once

#include <Wire.h>
#include "Print.h"

// commands
#define CMD_CLEARDISPLAY    = 0x01
#define CMD_RETURNHOME      = 0x02
#define CMD_ENTRYMODESET    = 0x04
#define CMD_DISPLAYCONTROL  = 0x08
#define CMD_CURSORSHIFT     = 0x10
#define CMD_FUNCTIONSET     = 0x20
#define CMD_SETCGRAMADDR    = 0x40
#define CMD_SETDDRAMADDR    = 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

class LCD
{
    public:
        LCD(int address, int sda_pin, int scl_pin);
        void printStr(const char* str);
        void backlight(bool on);
        void clearDisplay();
        void returnHome();
        void entryDir(bool forward);
        void show(bool show);
        uint8_t getRow() const {return 2;}
        uint8_t getCol() const {return 16;}
    private:
        size_t write(uint8_t byte);

        uint8_t addr_;
};
