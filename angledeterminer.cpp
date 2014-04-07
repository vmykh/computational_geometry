#include "angledeterminer.h"

#define PI 3.1415927

angleDeterminer::angleDeterminer()
{
}

double angleDeterminer::determineAngle(Vector v1, Vector v2)
{
    double sin_a = v1.crossProduct(v2) / (v1.Length() * v2.Length());
    double cos_a = v1.dotProduct(v2) / (v1.Length() * v2.Length());

    double alpha = sin_a >= 0 ? acos(cos_a) : 2 * PI - acos(cos_a);
    return alpha * 180 / PI;
}
