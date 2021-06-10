#pragma once

#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled!
#endif

constexpr uint32_t msgL = 21;

class Bluetooth
{
    public:
        Bluetooth();
        void init();
        void process();
    private:
        BluetoothSerial btSerial_;
        float north_ = 0.0;
        float east_ = 0.0;
        char messageChange_ = false;
        char message_[msgL];
        uint32_t messagePos_;
};
