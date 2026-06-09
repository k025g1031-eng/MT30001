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

float Determinant3x3(float m[3][3]) {

    return
        m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
        m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
        m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

float Determinant4x4(const Matrix4x4& m) {

    float det = 0.0f;

    for (int col = 0; col < 4; col++) {

        float sub[3][3];

        int subY = 0;

        for (int y = 1; y < 4; y++) {

            int subX = 0;

            for (int x = 0; x < 4; x++) {

                if (x == col) {
                    continue;
                }

                sub[subY][subX] = m.m[y][x];
                subX++;
            }

            subY++;
        }

        float sign = (col % 2 == 0) ? 1.0f : -1.0f;

        det += sign * m.m[0][col] * Determinant3x3(sub);
    }

    return det;
}
Matrix4x4 Inverse(const Matrix4x4& m) {

    Matrix4x4 result{};

    float det = Determinant4x4(m);

    if (det == 0.0f) {
        return MakeIdentity4x4();
    }

    Matrix4x4 cofactor{};

    for (int row = 0; row < 4; row++) {

        for (int col = 0; col < 4; col++) {

            float sub[3][3];

            int subY = 0;

            for (int y = 0; y < 4; y++) {

                if (y == row) {
                    continue;
                }

                int subX = 0;

                for (int x = 0; x < 4; x++) {

                    if (x == col) {
                        continue;
                    }

                    sub[subY][subX] = m.m[y][x];
                    subX++;
                }

                subY++;
            }

            float sign = ((row + col) % 2 == 0) ? 1.0f : -1.0f;

            cofactor.m[row][col] =
                sign * Determinant3x3(sub);
        }
    }

    Matrix4x4 adjugate = Transpose(cofactor);

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {

            result.m[y][x] =
                adjugate.m[y][x] / det;
        }
    }

    return result;
}