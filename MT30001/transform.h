#pragma once
#include"Vector3.h"
#include <cstdint>

struct Matrix4x4 {
    float m[4][4];
};

struct Sphere {
    Vector3 center; 
    float radius;
};

struct Line {
    Vector3 origin;
    Vector3 diff;
};

struct Ray {
    Vector3 origin;
    Vector3 diff;
};

struct Segment {
    Vector3 origin;
    Vector3 diff;
};

Vector3 Multiply(float scalar, const Vector3& vector);
float Dot(const Vector3& v1, const Vector3& v2);


Vector3 Subtract(const Vector3& v1, const Vector3& v2);

Vector3 Project(const Vector3& v1, const Vector3& v2);
Vector3 Add(const Vector3& v1, const Vector3& v2);

Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

Vector3 Cross(const Vector3& v1, const Vector3& v2);


Matrix4x4 MakeIdentity4x4();

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 MakeRotateYMatrix(float radian);

Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

Matrix4x4 MakePerspectiveFovMatrix(
    float fovY,
    float aspectRatio,
    float nearClip,
    float farClip);

Matrix4x4 MakeViewportMatrix(
    float left,
    float top,
    float width,
    float height,
    float minDepth,
    float maxDepth);

Matrix4x4 MakeOrthographicMatrix(
    float left,
    float top,
    float right,
    float bottom,
    float nearClip,
    float farClip);

Matrix4x4 Inverse(const Matrix4x4& m);

Matrix4x4 MakeAffineMatrix(
    const Vector3& scale,
    const Vector3& rotate,
    const Vector3& translate);

Vector3 Transform(
    const Vector3& vector,
    const Matrix4x4& matrix);

void DrawGrid(
    const Matrix4x4& viewProjectionMatrix,
    const Matrix4x4& viewportMatrix);

