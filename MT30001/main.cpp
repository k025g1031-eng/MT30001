#include <Novice.h>
#include <cstring>
#include "Vector3.h"
#include "Transform.h"

static const int kRowHeight = 20;
static const int kColumnWidth = 60;
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
    Novice::ScreenPrintf(x, y, "%.2f", vector.x);
    Novice::ScreenPrintf(x + kColumnWidth, y, "%.2f", vector.y);
    Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.2f", vector.z);
    Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
    Novice::ScreenPrintf(x, y, label);
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            Novice::ScreenPrintf(
                x + column * kColumnWidth,
                y + (20 + row * kRowHeight),
                "%6.02f",
                matrix.m[row][column]);
        }
    }
}

const char kWindowTitle[] = "GC2C_03_シュウ_シビ";

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // 三角形
    Vector3 kLocalVertices[3] = {
        { 0.0f,1.0f,0.0f},
        { 1.0f,-1.0f,0.0f},
        { -1.0f,-1.0f,0.0f},
    };

    Vector3 cameraPosition = { 0.0f,0.0f,-10.0f };

    Vector3 rotate{};
    Vector3 translate = { 0.0f,0.0f,2.0f };
    Vector3 Cross(const Vector3& v1, const Vector3& v2);

    Vector3 v1{ 1.2f,-3.9f,2.5f };
    Vector3 v2{ 2.8f,0.4f,-1.3f };
    Vector3 cross = Cross(v1, v2);
    

    while (Novice::ProcessMessage() == 0) {

        Novice::BeginFrame();

        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        ///
        /// ↓更新処理ここから
        ///

        // WS
        if (keys[DIK_W]) {
            translate.z += 0.05f;
        }

        if (keys[DIK_S]) {
            translate.z -= 0.05f;
        }

        // AD
        if (keys[DIK_A]) {
            translate.x -= 0.05f;
        }

        if (keys[DIK_D]) {
            translate.x += 0.05f;
        }

        // 自动旋转
        rotate.y += 0.02f;

        Matrix4x4 worldMatrix =
            MakeAffineMatrix(
                { 1.0f,1.0f,1.0f },
                rotate,
                translate);

        Matrix4x4 cameraMatrix =
            MakeAffineMatrix(
                { 1.0f,1.0f,1.0f },
                { 0.0f,0.0f,0.0f },
                cameraPosition);

        Matrix4x4 viewMatrix =
            Inverse(cameraMatrix);

        Matrix4x4 projectionMatrix =
            MakePerspectiveFovMatrix(
                0.45f,
                float(kWindowWidth) / float(kWindowHeight),
                0.1f,
                100.0f);

        Matrix4x4 worldViewProjectionMatrix =
            Multiply(
                worldMatrix,
                Multiply(
                    viewMatrix,
                    projectionMatrix));

        Matrix4x4 viewportMatrix =
            MakeViewportMatrix(
                0.0f,
                0.0f,
                float(kWindowWidth),
                float(kWindowHeight),
                0.0f,
                1.0f);

        Vector3 screenVertices[3];

        for (int i = 0; i < 3; i++) {

            Vector3 ndcVertex =
                Transform(
                    kLocalVertices[i],
                    worldViewProjectionMatrix);

            screenVertices[i] =
                Transform(
                    ndcVertex,
                    viewportMatrix);
        }

        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        ///

        Novice::DrawTriangle(
            int(screenVertices[0].x),
            int(screenVertices[0].y),

            int(screenVertices[1].x),
            int(screenVertices[1].y),

            int(screenVertices[2].x),
            int(screenVertices[2].y),

            RED,
            kFillModeSolid);
        VectorScreenPrintf(0, 0, cross, "Cross");

        ///
        /// ↑描画処理ここまで
        ///

        Novice::EndFrame();

        if (preKeys[DIK_ESCAPE] == 0 &&
            keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    Novice::Finalize();
    return 0;
}