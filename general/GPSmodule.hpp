#pragma once

#include "GPSreader.hpp"

struct Ecef
{
    int32_t x = 0;     // cm   
    int32_t y = 0;     // cm
    int32_t z = 0;     // cm
    uint32_t acc = 0;   // cm
};

struct Deg
{
    int32_t lat = 0;       // 1e-7
    int32_t lon = 0;       // 1e-7
    int32_t height = 0;    // mm   height above sea level
    uint32_t acc = 0;      // mm
};

class GPSmodule
{
    public:
        GPSmodule(HardwareSerial* serial);
        void init();
        void process();                     // call prediodically to process the messages
        Deg getDeg() const {return deg_;}
        Ecef getEcef() const {return ecef_;}
        uint8_t getFix() const {return fix_;}
        float getDegLatFloat() const {return deg_.lat / 10000000.0;}
        float getDegLonFloat() const {return deg_.lon / 10000000.0;}

        void print();
    private:
        GPSreader reader_;

        uint8_t fix_ = 0;
        Deg deg_;
        Ecef ecef_;
};
