#pragma once

#include <math.h>

class GPShelper
{
    public:
        static inline float degreesToRadians(float deg);
        static float distaceBetweenCoordinates(float lat1, float lon1, float lat2, float lon2);
};

