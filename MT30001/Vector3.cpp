#include "Vector3.h"
#include <math.h>

float Length(Vector3 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Normalize(Vector3 v) {
    float len = Length(v);

    if (len == 0) {
        return { 0.0f, 0.0f, 0.0f };
    }

    return { v.x / len, v.y / len, v.z / len };
}