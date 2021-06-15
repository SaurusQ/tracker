#pragma once

#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled!
#endif

#include "definitions.hpp"

constexpr uint32_t msgL = 21;

class Bluetooth
{
    public:
        Bluetooth();
        void init();
        void process();
        float getLat() { return lat_; }
        float getLon() { return lon_; }
    private:
        BluetoothSerial btSerial_;
        float lat_ = 0.0;
        float lon_ = 0.0;
        char messageChange_ = false;
        char message_[msgL];
        uint32_t messagePos_;
};
