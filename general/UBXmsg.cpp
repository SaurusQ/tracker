
#include "UBXmsg.hpp"

UBXmsg::UBXmsg(void* a, uint8_t* buff)
{
    std::memcpy(this, buff + HEADER_SIZE, *(uint16_t*)(buff + 2));
}

UBXmsg* parseUBX(uint8_t* buff)
{
    switch(*(uint32_t*)buff)
    {
    case NAV_POSLLH::hash:
        Serial.println("NAV_POSLLH");
        return new NAV_POSLLH(buff);
    case NAV_POSECEF::hash:
        Serial.println("NAV_POSCEF");
        return new NAV_POSECEF(buff);
    case NAV_PVT::hash:
        Serial.println("NAV_PVT");
        return new NAV_PVT(buff);
    case NAV_SOL::hash:
        Serial.println("NAV_SOL");
        return new NAV_SOL(buff);
    }
    Serial.println("nullptr");
    return nullptr;
}