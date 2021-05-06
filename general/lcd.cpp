
#include "lcd.hpp"

LCD::LCD(int sda_pin, int scl_pin)
{
    Wire1.begin(sda_pin, scl_pin, 40000);
}
