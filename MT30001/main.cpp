#include <Novice.h>
#include"transform.h"

const char kWindowTitle[] = "GC2C_03_シュウ_シビ";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y - 20, label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + (row)*kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {


	Novice::Initialize(kWindowTitle, 1280, 720);


	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	while (Novice::ProcessMessage() == 0) {

		Novice::BeginFrame();


		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		Matrix4x4 m1 = {
			3.2f, 0.7f, 9.6f, 4.4f,
			5.5f, 1.3f, 7.8f, 2.1f,
			6.9f, 8.0f, 2.6f, 1.0f,
			0.5f, 7.2f, 5.1f, 3.3f };
		Matrix4x4 m2 = {
			4.1f,6.5f,3.3f,2.2f,
			8.8f,0.6f,9.9f,7.7f,
			1.1f,5.5f,6.6f,0.0f,
			3.3f,9.9f,8.8f,2.2f };

		Matrix4x4 resultAdd = Add(m1, m2);
		Matrix4x4 resultMultiply = Multiply(m1, m2);
		Matrix4x4 resultSubtract = Subtract(m1, m2);
		Matrix4x4 inverseM1 = Inverse(m1);
		Matrix4x4 inverseM2 = Inverse(m2);
		Matrix4x4 transposeM1 = Transpose(m1);
		Matrix4x4 transposeM2 = Transpose(m2);
		Matrix4x4 identity = MakeIdentity4x4();
		MatrixScreenPrintf(0, 20, resultAdd, "Add");
		MatrixScreenPrintf(0, (20 + kRowHeight * 5), resultSubtract, "Subtract");
		MatrixScreenPrintf(0, (20 + kRowHeight * 5 * 2), resultMultiply, "Multiply");
		MatrixScreenPrintf(0, (20 + kRowHeight * 5 * 3), inverseM1, "inverseM1");
		MatrixScreenPrintf(0, (20 + kRowHeight * 5 * 4), inverseM2, "inverseM2");
		MatrixScreenPrintf(kColumnWidth * 5, 20, transposeM1, "transposeM1");
		MatrixScreenPrintf(kColumnWidth * 5, (20 + kRowHeight * 5), transposeM2, "transposeM2");
		MatrixScreenPrintf(kColumnWidth * 5, (20 + kRowHeight * 5 * 2), identity, "identity");


		Novice::EndFrame();


		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	Novice::Finalize();
	return 0;
}
