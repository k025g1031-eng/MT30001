#include"transform.h"
#include <cmath>

Matrix4x4 MakeRotateXMatrix(float radian) {
    Matrix4x4 result = {
        {
            {1.0f, 0.0f,              0.0f,             0.0f},
            {0.0f, std::cos(radian),  std::sin(radian), 0.0f},
            {0.0f,-std::sin(radian),  std::cos(radian), 0.0f},
            {0.0f, 0.0f,              0.0f,             1.0f}
        }
    };

    return result;
}
Matrix4x4 MakeRotateYMatrix(float radian) {
    Matrix4x4 result = {
        {
            { std::cos(radian), 0.0f,-std::sin(radian), 0.0f},
            { 0.0f,             1.0f, 0.0f,             0.0f},
            { std::sin(radian), 0.0f, std::cos(radian), 0.0f},
            { 0.0f,             0.0f, 0.0f,             1.0f}
        }
    };

    return result;
}
Matrix4x4 MakeRotateZMatrix(float radian) {
    Matrix4x4 result = {
        {
            { std::cos(radian),  std::sin(radian), 0.0f, 0.0f},
            {-std::sin(radian),  std::cos(radian), 0.0f, 0.0f},
            { 0.0f,              0.0f,             1.0f, 0.0f},
            { 0.0f,              0.0f,             0.0f, 1.0f}
        }
    };

    return result;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {

    Matrix4x4 result{};

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {

            result.m[y][x] =
                m1.m[y][0] * m2.m[0][x] +
                m1.m[y][1] * m2.m[1][x] +
                m1.m[y][2] * m2.m[2][x] +
                m1.m[y][3] * m2.m[3][x];

        }
    }

    return result;
}

