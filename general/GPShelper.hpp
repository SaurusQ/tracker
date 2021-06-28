#pragma once

#include <math.h>

enum Dir
{
    N  = 0,
    NE = 1,
    E  = 2,
    SE = 3,
    S  = 4,
    SW = 5,
    W  = 6,
    NW = 7
};

class GPShelper
{
    public:
        static inline Dir angleToDir(float angle);
        static inline float degreesToRadians(float deg);
        static inline float radiansToDegrees(float rad);
        static float distaceBetweenCoordinates(float lat1, float lon1, float lat2, float lon2);
        static Dir bearing(float lat1, float lon1, float lat2, float lon2);
};

