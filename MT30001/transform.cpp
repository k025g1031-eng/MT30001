#include "Transform.h"

#include <cmath>

Vector3 Cross(const Vector3& v1, const Vector3& v2) {

    Vector3 result;

    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;

    return result;
}

Matrix4x4 MakeIdentity4x4() {

    Matrix4x4 result{};

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (x == y) {
                result.m[y][x] = 1.0f;
            }
            else {
                result.m[y][x] = 0.0f;
            }
        }
    }

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

Matrix4x4 MakeRotateYMatrix(float radian) {

    Matrix4x4 result = MakeIdentity4x4();

    result.m[0][0] = cosf(radian);
    result.m[0][2] = sinf(radian);

    result.m[2][0] = -sinf(radian);
    result.m[2][2] = cosf(radian);

    return result;
}

Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {

    Matrix4x4 result = MakeIdentity4x4();

    result.m[3][0] = translate.x;
    result.m[3][1] = translate.y;
    result.m[3][2] = translate.z;

    return result;
}

Matrix4x4 MakePerspectiveFovMatrix(
    float fovY,
    float aspectRatio,
    float nearClip,
    float farClip) {

    Matrix4x4 result{};

    float cot = 1.0f / tanf(fovY / 2.0f);

    result.m[0][0] = cot / aspectRatio;
    result.m[1][1] = cot;
    result.m[2][2] = farClip / (farClip - nearClip);
    result.m[2][3] = 1.0f;
    result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);

    return result;
}

Matrix4x4 MakeOrthographicMatrix(
    float left,
    float top,
    float right,
    float bottom,
    float nearClip,
    float farClip) {

    Matrix4x4 result{};

    result.m[0][0] = 2.0f / (right - left);
    result.m[1][1] = 2.0f / (top - bottom);
    result.m[2][2] = 1.0f / (farClip - nearClip);

    result.m[3][0] = (left + right) / (left - right);
    result.m[3][1] = (top + bottom) / (bottom - top);
    result.m[3][2] = nearClip / (nearClip - farClip);
    result.m[3][3] = 1.0f;

    return result;
}

Matrix4x4 MakeViewportMatrix(
    float left,
    float top,
    float width,
    float height,
    float minDepth,
    float maxDepth) {

    Matrix4x4 result{};

    result.m[0][0] = width / 2.0f;
    result.m[1][1] = -height / 2.0f;
    result.m[2][2] = maxDepth - minDepth;

    result.m[3][0] = left + width / 2.0f;
    result.m[3][1] = top + height / 2.0f;
    result.m[3][2] = minDepth;
    result.m[3][3] = 1.0f;

    return result;
}

Matrix4x4 Inverse(const Matrix4x4& m) {

    Matrix4x4 a = m;
    Matrix4x4 result = MakeIdentity4x4();

    for (int i = 0; i < 4; i++) {

        float pivot = a.m[i][i];

        for (int j = 0; j < 4; j++) {
            a.m[i][j] /= pivot;
            result.m[i][j] /= pivot;
        }

        for (int k = 0; k < 4; k++) {

            if (k == i) {
                continue;
            }

            float factor = a.m[k][i];

            for (int j = 0; j < 4; j++) {
                a.m[k][j] -= factor * a.m[i][j];
                result.m[k][j] -= factor * result.m[i][j];
            }
        }
    }

    return result;
}

Matrix4x4 MakeAffineMatrix(
    const Vector3& scale,
    const Vector3& rotate,
    const Vector3& translate) {

    Matrix4x4 result{};

    float cx = cosf(rotate.x);
    float sx = sinf(rotate.x);

    float cy = cosf(rotate.y);
    float sy = sinf(rotate.y);

    float cz = cosf(rotate.z);
    float sz = sinf(rotate.z);

    result.m[0][0] = scale.x * (cy * cz);
    result.m[0][1] = scale.x * (cy * sz);
    result.m[0][2] = scale.x * (-sy);
    result.m[0][3] = 0.0f;

    result.m[1][0] = scale.y * (sx * sy * cz - cx * sz);
    result.m[1][1] = scale.y * (sx * sy * sz + cx * cz);
    result.m[1][2] = scale.y * (sx * cy);
    result.m[1][3] = 0.0f;

    result.m[2][0] = scale.z * (cx * sy * cz + sx * sz);
    result.m[2][1] = scale.z * (cx * sy * sz - sx * cz);
    result.m[2][2] = scale.z * (cx * cy);
    result.m[2][3] = 0.0f;

    result.m[3][0] = translate.x;
    result.m[3][1] = translate.y;
    result.m[3][2] = translate.z;
    result.m[3][3] = 1.0f;

    return result;
}

Vector3 Transform(
    const Vector3& vector,
    const Matrix4x4& matrix) {

    Vector3 result;

    float w;

    result.x =
        vector.x * matrix.m[0][0] +
        vector.y * matrix.m[1][0] +
        vector.z * matrix.m[2][0] +
        matrix.m[3][0];

    result.y =
        vector.x * matrix.m[0][1] +
        vector.y * matrix.m[1][1] +
        vector.z * matrix.m[2][1] +
        matrix.m[3][1];

    result.z =
        vector.x * matrix.m[0][2] +
        vector.y * matrix.m[1][2] +
        vector.z * matrix.m[2][2] +
        matrix.m[3][2];

    w =
        vector.x * matrix.m[0][3] +
        vector.y * matrix.m[1][3] +
        vector.z * matrix.m[2][3] +
        matrix.m[3][3];

    if (w != 0.0f) {
        result.x /= w;
        result.y /= w;
        result.z /= w;
    }

    return result;
}