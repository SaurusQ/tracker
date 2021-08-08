#include "GPShelper.hpp"

Dir GPShelper::angleToDir(float angle)
{
    constexpr float div = (360.0f / 8.0f);
    return static_cast<Dir>(static_cast<int>((angle + (div / 2.0f)) / (div)) % 8);
}

float GPShelper::degreesToRadians(float deg)
{
    return deg * M_PI / 180.0f;
}

float GPShelper::radiansToDegrees(float rad)
{
    return rad * 180.0f / M_PI;
}

float GPShelper::distaceBetweenCoordinates(float lat1, float lon1, float lat2, float lon2)
{
    constexpr float earthRadiusKm = 6371;

    float dLat = degreesToRadians(lat2-lat1);
    float dLon = degreesToRadians(lon2-lon1);

    lat1 = degreesToRadians(lat1);
    lat2 = degreesToRadians(lat2);

    float a = sin(dLat/2) * sin(dLat/2) +
          sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2); 
    float c = 2 * atan2(sqrt(a), sqrt(1-a));
    return earthRadiusKm * c;
}

Dir GPShelper::bearing(float lat1, float lon1, float lat2,float lon2)
{
    float teta1  = degreesToRadians(lat1);
    float teta2  = degreesToRadians(lat2);
    //float delta1 = degreesToRadians(lat2 - lat1);
    float delta2 = degreesToRadians(lon2 - lon1);

    float y = sin(delta2) * cos(teta2);
    float x = cos(teta1) * sin(teta2) - sin(teta1) * cos(teta2) * cos(delta2);
    float brng = atan2(y,x);
    brng = radiansToDegrees(brng);
    brng = ((int)brng + 360) % 360; 

    return angleToDir(brng);
}
