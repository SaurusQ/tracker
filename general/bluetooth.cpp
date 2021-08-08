#include "bluetooth.hpp"

Bluetooth::Bluetooth()
{
}

void Bluetooth::init()
{
    btSerial_.begin("ESP32test");
}

void Bluetooth::process()
{
    while(btSerial_.available() > 0)
    {
        char inByte = btSerial_.read();
        message_[messagePos_] = inByte;
        messagePos_++;
        messageChange_ = true;
    }

    messagePos_ = 0;

    if(messageChange_)
    {
        LOG("Bluetooth got message");
        hasTarget_ = true;
        char bfr[9];
        String msg = message_;

        msg.substring(0, 9).toCharArray(bfr, 9);
        LOG(bfr);
        lat_ = atof(bfr);
        msg.substring(11, 20).toCharArray(bfr, 9);
        LOG(bfr);
        lon_ = atof(bfr);

        LOG(message_);
        LOG(lat_*1000000);
        LOG(lon_*1000000);
        messageChange_ = false;
    }
}
