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

Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
    Matrix4x4 result = MakeIdentity4x4();    
    result.m[3][0] = translate.x;    
    result.m[3][1] = translate.y;    
    result.m[3][2] = translate.z;    
    return result; 

}

Matrix4x4 MakeScaleMatrix(const Vector3& scale) { 
    Matrix4x4 result = MakeIdentity4x4();    
    result.m[0][0] = scale.x;    
    result.m[1][1] = scale.y;    
    result.m[2][2] = scale.z;    
    return result; 
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) { 
    Vector3 result;    
    result.x = vector.x * matrix.m[0][0] + 
        vector.y * matrix.m[1][0] + 
        vector.z * matrix.m[2][0] + 
        1.0f * matrix.m[3][0];   
    
    result.y = vector.x * matrix.m[0][1] + 
        vector.y * matrix.m[1][1] + 
        vector.z * matrix.m[2][1] + 
        1.0f * matrix.m[3][1];    
    
    result.z = vector.x * matrix.m[0][2] + 
        vector.y * matrix.m[1][2] + 
        vector.z * matrix.m[2][2] + 
        1.0f * matrix.m[3][2];    
    
    return result; 

}

Matrix4x4 MakeAffineMatrix(
    const Vector3& scale,
    const Vector3& rotate,
    const Vector3& translate)
{
    Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

    Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
    Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
    Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);

    Matrix4x4 rotateMatrix =
        Multiply(
            rotateXMatrix,
            Multiply(rotateYMatrix, rotateZMatrix)
        );

    Matrix4x4 translateMatrix =
        MakeTranslateMatrix(translate);

    Matrix4x4 worldMatrix =
        Multiply(
            scaleMatrix,
            Multiply(
                rotateMatrix,
                translateMatrix
            )
        );

    return worldMatrix;
}