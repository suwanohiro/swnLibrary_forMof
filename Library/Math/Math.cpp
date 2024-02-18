#include "Math.hpp"

using namespace swn;

double Math::toRadian(double deg)
{
    return deg * pi * DEG_TO_RAD_FACTOR;
}

