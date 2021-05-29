#pragma once

#include <cstring>
#include <Arduino.h>
#include "definitions.hpp"

class UBXmsg;
UBXmsg* parseUBX(uint8_t* buff);

enum UBX_TYPE
{
    E_NAV_POSLLH,
    E_NAV_POSECEF,
    E_NAV_PVT,
    E_NAV_SOL
};

#define HASH(c, id, len) ((c & 0xFF) << 0) | ((id & 0xFF) << 8) | ((len & 0xFFFF) << 16)


class UBXmsg
{
    public:
        UBXmsg(void* a, uint8_t* buff);
        static constexpr uint32_t getHash();
        virtual UBX_TYPE getType() = 0;
        virtual String toString() = 0;
};

class NAV_POSLLH : public UBXmsg
{
    public:
        NAV_POSLLH(uint8_t* buff) : UBXmsg(this, buff) {}
        static constexpr uint32_t hash = HASH(0x01, 0x02, 28);
        virtual UBX_TYPE getType() { return UBX_TYPE::E_NAV_POSLLH; };
        virtual String toString() {
            return "NAV_POSLLH\nLon: " + String(lon) + "\n" + "Lat: " + String(lat);
        }
        // Type     Name    Unit    Description (scaling)
        uint32_t    iTOW;   // ms   GPS time of week of the navigation epoch
        int32_t     lon;    // deg  Longitude (1e-7)
        int32_t     lat;    // deg  Latitude (1e-7)
        int32_t     height; // mm   Height above ellipsoid
        int32_t     hMSL;   // mm   Height above mean sea level
        uint32_t    hAcc;   // mm   Horizontal accuracy estimate
        uint32_t    vAcc;   // mm   Vertical accuracy estimate
};

class NAV_POSECEF : public UBXmsg
{
    public:
        NAV_POSECEF(uint8_t* buff) : UBXmsg(this, buff) {}
        static constexpr uint32_t hash = HASH(0x01, 0x01, 20);
        virtual UBX_TYPE getType() { return UBX_TYPE::E_NAV_POSECEF; }
        virtual String toString() {
            return "NAV_POSECEF\nAccuracy: " + String(pAcc);
        }

        // Type     Name    Unit    Description (scaling)
        uint32_t    iTOW;   // ms   GPS time of week of the navigation epoch
        int32_t     ecefX;  // cm   ECEF X coordinate
        int32_t     ecefY;  // cm   ECEF Y coordinate
        int32_t     ecefZ;  // cm   ECEF Z coordinate
        uint32_t    pAcc;   // cm   Position Accuracy Estimate
};

class NAV_PVT : public UBXmsg
{
    public:
        NAV_PVT(uint8_t* buff) : UBXmsg(this, buff) {}
        static constexpr uint32_t hash = HASH(0x01, 0x07, 92);
        virtual UBX_TYPE getType() { return UBX_TYPE::E_NAV_PVT; }
        virtual String toString() {
            return "NAV_PVT\nLon: " + String(lon) + "\n" + "Lat: " + String(lat);
        }

        // Type     Name        Unit        Description (scaling)
        uint32_t    iTOW;       // ms       GPS time of week of the navigation epoch
        uint16_t    year;       // y        Year UTC
        uint8_t     month;      // month    Month, range 1..12 UTC
        uint8_t     day;        // d        Day of month, range 1..31 UTC
        uint8_t     hour;       // h        Hour of day, range 0..23 UTC
        uint8_t     min;        // min      Minute of hour, range 0..59 UTC
        uint8_t     sec;        // s        Seconds of minute, range 0..60 UTC
        uint8_t     valid;      // -        Validity Flags
        uint32_t    tAcc;       // ns       Time accuracy estimate UTC
        int32_t     nano;       // ns       Fraction of second, range -1e9..1e9 UTC
        uint8_t     fixType;    // -        GNSSfix Type, range 0..5
        uint8_t     flags;      // -        Fix Status Flags
        uint8_t     flags2;     // -        Additional flags
        uint8_t     numSV;      // -        Number of satellites used in Nav Solution
        int32_t     lon;        // deg      Longitude (1e-7)
        int32_t     lat;        // deg      Latitude (1e-7)
        int32_t     height;     // mm       Height above Ellipsoid
        int32_t     hMSL;       // mm       Height above mean sea level
        uint32_t    hAcc;       // mm       Horizontal Accuracy Estimate
        uint32_t    vAcc;       // mm       Vertical Accuracy Estimate
        int32_t     velN;       // mm/s     NED north velocity
        int32_t     velE;       // mm/s     NED east velocity
        int32_t     velD;       // mm/s     NED down velocity
        int32_t     gSpeed;     // mm/s     Ground Speed (2-D)
        int32_t     headMot;    // deg      Heading of motion 2-D (1e-5)
        uint32_t    sAcc;       // mm/s     Speed Accuracy Estimate
        uint32_t    headingAcc; // deg      Heading Accuracy Estimate (1e-5)
        uint16_t    pDOP;       // -        Position DOP (0.01)
        uint8_t     flags3;     // -        Additional flags
        uint8_t     reserved1;  // -        Reserved
        uint8_t     reserved2;  // -        Reserved
        uint8_t     reserved3;  // -        Reserved
        uint8_t     reserved4;  // -        Reserved
        uint8_t     reserved5;  // -        Reserved
        int32_t     headVeh;    // deg      Heading of vehicle (1e-5)
        int16_t     magDec;     // deg      Magnetic declination (1e-2)
        uint16_t    magAcc;     // deg      Magnetic accuracy (1e-2)
};

class NAV_SOL : public UBXmsg
{
    public:
        NAV_SOL(uint8_t* buff) : UBXmsg(this, buff) {}
        static constexpr uint32_t hash = HASH(0x01, 0x06, 52);
        virtual UBX_TYPE getType() { return UBX_TYPE::E_NAV_SOL; }
        virtual String toString() {
            return "NAV_SOL\nSatellites: " + String(numSV) + "\n" + "gpsFix: " + String(gpsFix);
        }

        // Type     Name        Unit        Description (scaling)
        uint32_t    iTOW;       // ms       GPS time of week of the navigation epoch. See the description of iTOW for
        int32_t     fTOW;       // ns       Fractional part of iTOW (range: +/-500000). The precise GPS time of week in
                                //          seconds is: (iTOW * 1e-3) + (fTOW * 1e-9)
        int16_t     week;       // weeks    GPS week number of the navigation epoch
        uint8_t     gpsFix;     // -        GPSfix Type, range 0..5
        int8_t      flags;      // -        Fix Status Flags (see graphic below)
        int32_t     ecefX;      // cm       ECEF X coordinate
        int32_t     ecefY;      // cm       ECEF Y coordinate
        int32_t     ecefZ;      // cm       ECEF Z coordinate
        uint32_t    pAcc;       // cm       3D Position Accuracy Estimate
        int32_t     ecefVX;     // cm/s     ECEF X velocity
        int32_t     ecefVY;     // cm/s     ECEF Y velocity
        int32_t     ecefVZ;     // cm/s     ECEF Z velocity
        uint32_t    sAcc;       // cm/s     Speed Accuracy Estimate
        uint16_t    pDOP;       // -        Position DOP (0.01)
        uint8_t     reserved1;  // -        Reserved
        uint8_t     numSV;      // -        Number of satellites used in Nav Solution
        uint32_t    reserved2;  // -        Reserved
};
