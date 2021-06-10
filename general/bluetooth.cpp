#include "bluetooth.hpp"

Bluetooth::Bluetooth()
{
}

void Bluetooth::init()
{
    SerialBT.begin("ESP32test");
}

Bluetooth::process()
{
    while(SerialBT.available() > 0)
    {
        char inByte = SerialBT.read();
        message_[messagePos_] = inByte;
        messagePos_++;
        messageChange_ = true;
    }

    messagePos_ = 0;

    if(messageChange_)
    {
        char bfr[9];
        String msg = message;

        msg.substring(0, 9).toCharArray(bfr, 9);
        north_ = atof(bfr);
        msg.substring(11, 9).toCharArray(bfr, 9);
        east_ = atof(bfr);

        LOG(message_);
        LOG(north_*1000000);
        LOG(east_*1000000);
        messageChange_ = false;
    }
}
