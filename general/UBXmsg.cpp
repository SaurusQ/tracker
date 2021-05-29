
#include "UBXmsg.hpp"

UBXmsg::UBXmsg(void* a, uint8_t* buff)
{
    std::memcpy(((uint8_t*)this) + 4u, buff + 4u, *(uint16_t*)(buff + 2));
}

UBXmsg* parseUBX(uint8_t* buff)
{
    switch(*(uint32_t*)buff)
    {
    case NAV_POSLLH::hash:
        return new NAV_POSLLH(buff);
    case NAV_POSECEF::hash:
        return new NAV_POSECEF(buff);
    case NAV_PVT::hash:
        return new NAV_PVT(buff);
    case NAV_SOL::hash:
        return new NAV_SOL(buff);
    default:
        return nullptr;
    }
}