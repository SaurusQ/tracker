
#pragma once

#include <Wire.h>

class LCD
{
    public:
        LCD(int sda_pin, int scl_pin);
        
    private:
        const int address = 0x27;
};
