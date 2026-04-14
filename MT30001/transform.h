#pragma once
#include "vector3.h"

struct Matrix4x4 {
    float m[4][4];
};

Vector3 Add(const Vector3& v1, const Vector3& v2);
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
Vector3 Multiply(const float scalar, const Vector3& v1);
float Dot(const Vector3& v1, const Vector3& v2);
