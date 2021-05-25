
#include "GPSmodule.hpp"

GPSmodule::GPSmodule(HardwareSerial* serial)
    : reader_(GPSreader(serial))
{

}

void GPSmodule::process()
{
    UBXmsg* msg = reader_.process();
    if(msg != nullptr)
    {
        LOG("Message found");
        LOG(msg->toString());
        switch(msg->getType())
        {
            case UBX_TYPE::E_NAV_POSECEF:
                ecef_.x = ((NAV_POSECEF*)msg)->ecefX;
                ecef_.y = ((NAV_POSECEF*)msg)->ecefY;
                ecef_.x = ((NAV_POSECEF*)msg)->ecefZ;
                ecef_.acc = ((NAV_POSECEF*)msg)->pAcc;
                break;
            case UBX_TYPE::E_NAV_POSLLH:
                deg_.lat = ((NAV_POSLLH*)msg)->lat;
                deg_.lon = ((NAV_POSLLH*)msg)->lon;
                deg_.height = ((NAV_POSLLH*)msg)->hMSL;
                deg_.acc = ((NAV_POSLLH*)msg)->hAcc;
                break;
            case UBX_TYPE::E_NAV_SOL:
                fix_ = ((NAV_SOL*)msg)->gpsFix;
                break;
            case UBX_TYPE::E_NAV_PVT:
                break;
            default:
                LOG("Message type not implemented");
                break;

        }
    }
}

void GPSmodule::print()
{
    Serial.println("GPSmodule information:");
    Serial.print("lat: ");
    Serial.println(deg_.lat);
    Serial.print("lon: ");
    Serial.println(deg_.lon);
    Serial.print("fix: ");
    Serial.println(fix_);
}
