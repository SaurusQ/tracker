
#include "GPSreader.hpp"

GPSreader::GPSreader(HardwareSerial* serial)
    : serial_(serial)
{

}

void GPSreader::init()
{
    const uint8_t* data = configData;
    for(int i = 0; i < CFG_MSG_NUM; i++)
    {
        serial_->write(data, CFG_MSG_LEN);
        data += CFG_MSG_LEN;
        delay(10);
        while(serial_->available()) serial_->read();
    }
}

UBXmsg* GPSreader::process()
{
    if(this->readMsg())
    {
        if(this-checksum())
        {
            Serial.print("Correct checksum\n");
            return parseUBX(buff_);
        }
        else
        {
            Serial.print("Wrong checksum\n");
        }
    }
    return nullptr;
}

bool GPSreader::readMsg()
{
    Serial.println("readMsg");
    if(!onSync)
    {
        LOG("Trying to sync");
        if(!this->sync()) return false;
        onSync = true;
    }
    if(!headerRead)
    {
        // Read the header
        LOG("Trying to read the header");
        if(serial_->available() < 4) return false;
        serial_->readBytes(buff_, 4);
        // class
        c_ = buff_[0];
        id_ = buff_[1];
        len_ = *(uint16_t*)(buff_ + 2);
        headerRead = true;
        LOG("Lenght: " + String(len_));
        if(len_ > 100) // just for that the sync problems are resolved faster 
        {
            headerRead = false;
            onSync = false;
            return false;
        }
    }
    if(serial_->available() >= len_)
    {
        LOG("Trying to read the msg");
        // read rest of the message + check sum of 2
        serial_->readBytes(buff_ + HEADER_SIZE, len_ + 2);
        ck_a_ = (buff_ + HEADER_SIZE + len_)[0];
        ck_b_ = (buff_ + HEADER_SIZE + len_)[1];
        headerRead = false;
        onSync = false;
        return true;
    }
    return false;
}

bool GPSreader::sync()
{
    while(serial_->available() >= 2)
    {
        if(serial_->read() != 0xB5) continue;
        if(serial_->peek() != 0x62) continue;
        serial_->read();
        return true;
    }
    return false;
}

bool GPSreader::checksum()
{
    uint8_t CK_A = 0;
    uint8_t CK_B = 0;
    for(int i = 0; i < len_ + HEADER_SIZE; i++)
    {
        CK_A += buff_[i];
        CK_B += CK_A;
    }
    // correct checksum?
    return ck_a_ == CK_A && ck_b_ == CK_B;
}
