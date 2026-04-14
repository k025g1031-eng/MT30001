#pragma once
struct Vector3 {
    float x;
    float y;
    float z;
};

float length(Vector3 v);
Vector3 normalize(Vector3 v);

