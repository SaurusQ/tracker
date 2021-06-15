#include "GPShelper.hpp"

float GPShelper::degreesToRadians(float deg)
{
    return deg * M_PI / 180.0f;
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