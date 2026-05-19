#include "Transform.h"


Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {

    Matrix4x4 result{};

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {

            result.m[y][x] = m1.m[y][x] + m2.m[y][x];

        }
    }

    return result;
}

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {

    Matrix4x4 result{};

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {

            result.m[y][x] = m1.m[y][x] - m2.m[y][x];

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


Matrix4x4 Transpose(const Matrix4x4& m) {

    Matrix4x4 result{};

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {

            result.m[y][x] = m.m[x][y];

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

Matrix4x4 Inverse(const Matrix4x4& m) {

    (void)m;

    Matrix4x4 result = MakeIdentity4x4();

    return result;
}