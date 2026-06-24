#include "../include/haversine.hpp"

#include <cmath>

static constexpr double R = 6371000.0;

double haversine(
    double lat1,
    double lon1,
    double lat2,
    double lon2
)
{
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;

    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    double a =
        sin(dLat/2) * sin(dLat/2)
        +
        cos(lat1)
        *
        cos(lat2)
        *
        sin(dLon/2)
        *
        sin(dLon/2);

    double c =
        2.0 * atan2(
            sqrt(a),
            sqrt(1-a)
        );

    return R * c;
}