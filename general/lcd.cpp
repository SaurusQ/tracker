
#include "lcd.hpp"
#include "definitions.hpp"

LCD::LCD(int address, int sda_pin, int scl_pin)
    : addr_(address)
{
    Wire1.begin(sda_pin, scl_pin, 40000);
    delay(300);
    this->write(0x03);
    delay(300);
    this->write(0x03);
    delay(300);
    this->write(0x03);
    delay(300);
    this->write(0x02);
}

void LCD::printStr(const char* str)
{
    while(str[0] != '\0')
    {
        this->write(str[0]);
        str++;
    }
}

void LCD::backlight(bool on)
{
    this->write(0b00001000 | (on << 3));
}

void LCD::clearDisplay()
{
    this->write(0x1);
}

void LCD::returnHome()
{
    this->write(0x2);
}

void LCD::entryDir(bool forward)
{
    this->write(0x4 | (forward << 1) | 0x0);
}

void LCD::show(bool show)
{
    LOG(0x8 | (show << 2) | (0x0 << 1) | 0x0);
    this->write(0x8 | (show << 2) | (0x0 << 1) | 0x0);
}

size_t LCD::write(uint8_t byte)
{
    Wire1.beginTransmission(addr_);
    Wire1.write(byte);
    Wire1.endTransmission();
    return 1u; // no error handling
}
