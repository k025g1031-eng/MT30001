#include <Novice.h>
#include <cstring>
#include <imgui.h>
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


    Segment segment{ {-2.0f,-1.0f,0.0f},{3.0f, 2.0f, 2.0f} };
    Vector3 point{ -1.5f, 0.6f, 0.6f };

    Vector3 project{};
    Vector3 closestPoint{};

   Vector3 cameraTranslate{0.0f, 1.9f, -6.49f};
    Vector3 cameraRotate{ 0.0f,0.0f,0.0f };

 

    while (Novice::ProcessMessage() == 0) {

        Novice::BeginFrame();

        ImGui::Begin("Control");

        ImGui::DragFloat3("Camera Translate", &cameraTranslate.x, 0.01f);
        ImGui::DragFloat3("Camera Rotate", &cameraRotate.x, 0.01f);
        ImGui::DragFloat3("Point", &point.x, 0.01f);

        ImGui::DragFloat3("Segment Origin", &segment.origin.x, 0.01f);

        ImGui::DragFloat3("Segment Diff", &segment.diff.x, 0.01f);

        ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);

        ImGui::End();

        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        ///
        /// ↓更新処理ここから
        ///

        project = Project(
            Subtract(point, segment.origin),
            segment.diff);

        closestPoint = ClosestPoint(
            point,
            segment);

        Sphere pointSphere{ 
            point,
            0.01f
        };

        Sphere closestPointSphere{
            closestPoint,
            0.01f
        };

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
            pointSphere,
            viewProjectionMatrix,
            viewportMatrix,
            RED);

        DrawSphere(
            closestPointSphere,
            viewProjectionMatrix,
            viewportMatrix,
            BLACK);

        Vector3 start =
            Transform(
                Transform(segment.origin, viewProjectionMatrix),
                viewportMatrix);

        Vector3 end =
            Transform(
                Transform(
                    Add(segment.origin, segment.diff),
                    viewProjectionMatrix),
                viewportMatrix);

        Novice::DrawLine(
            int(start.x),
            int(start.y),
            int(end.x),
            int(end.y),
            WHITE);


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