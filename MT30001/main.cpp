#include <Novice.h>
#include <cstring>
#include <imgui.h>
#include "Vector3.h"
#include "Transform.h"
#include"collision.h"

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


    Vector3 v1{ 1.2f,-3.9f,2.5f };
    Vector3 v2{ 2.8f,0.4f,-1.3f };
    Vector3 cross = Cross(v1, v2);

    Vector3 cameraTranslate{0.0f, 1.9f, -6.49f};
    Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

    Sphere sphere1{
    { -2.0f,0.0f,0.0f },
    1.0f
    };


    Sphere sphere2{
        { 2.0f,0.0f,0.0f },
        1.0f
    };
    

    while (Novice::ProcessMessage() == 0) {

        Novice::BeginFrame();

        ImGui::Begin("Sphere");


        ImGui::DragFloat3(
            "Sphere1 Center",
            &sphere1.center.x,
            0.01f
        );


        ImGui::DragFloat(
            "Sphere1 Radius",
            &sphere1.radius,
            0.01f
        );



        ImGui::DragFloat3(
            "Sphere2 Center",
            &sphere2.center.x,
            0.01f
        );


        ImGui::DragFloat(
            "Sphere2 Radius",
            &sphere2.radius,
            0.01f
        );


        ImGui::End();

        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        ///
        /// ↓更新処理ここから
        ///

       
        Matrix4x4 cameraMatrix =
            MakeAffineMatrix(
                { 1.0f,1.0f,1.0f },
                cameraRotate,
                cameraTranslate);

        Matrix4x4 viewMatrix =
            Inverse(cameraMatrix);

        Matrix4x4 projectionMatrix =
            MakePerspectiveFovMatrix(
                0.45f,
                float(kWindowWidth) / float(kWindowHeight),
                0.1f,
                100.0f);

        Matrix4x4 viewProjectionMatrix =
            Multiply(
                viewMatrix,
                projectionMatrix);

        Matrix4x4 viewportMatrix =
            MakeViewportMatrix(
                0.0f,
                0.0f,
                float(kWindowWidth),
                float(kWindowHeight),
                0.0f,
                1.0f);

        uint32_t color1 = WHITE;
        uint32_t color2 = WHITE;


        if (IsCollision(sphere1, sphere2))
        {
            color2 = RED;
        }

        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        ///

        DrawGrid(
            viewProjectionMatrix,
            viewportMatrix);

        DrawSphere(
            sphere1,
            viewProjectionMatrix,
            viewportMatrix,
            color1
        );


        DrawSphere(
            sphere2,
            viewProjectionMatrix,
            viewportMatrix,
            color2
        );

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