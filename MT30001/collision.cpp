#include "Collision.h"
#include <cmath>


bool IsCollision(const Sphere& s1, const Sphere& s2)
{

    float distance =
        sqrtf(
            (s1.center.x - s2.center.x) *
            (s1.center.x - s2.center.x)

            +

            (s1.center.y - s2.center.y) *
            (s1.center.y - s2.center.y)

            +

            (s1.center.z - s2.center.z) *
            (s1.center.z - s2.center.z)
        );


    if (distance <= s1.radius + s2.radius)
    {
        return true;
    }


    return false;
}