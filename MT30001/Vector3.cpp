#include "vector3.h"
#include <math.h>

float length(Vector3 v) {
    return sqrtf(v.x * v.x + v.y * v.y+v.z*v.z);
}

Vector3 normalize(Vector3 v) {
    float len = length(v);
    if (len == 0) return { 0, 0 };
    return { v.x / len, v.y / len,v.z/len };
}