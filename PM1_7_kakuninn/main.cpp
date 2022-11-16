#include <Novice.h>

#define _USE_MATH_DEFINES
#include <math.h>

/*================================
	コピペ用↓
=================================*/

/*********************************
    大見出しコピペ
*********************************/

/******** 小見出しコピペ用 **********/

/*================================
    コピペ用↑
=================================*/

/******** ウィンドウ名の指定 **********/
const char kWindowTitle[] = "LC1A_16_トヨダユウキ_PM1_7_課題";

/******** ウィンドウサイズの指定 **********/
const int kWinodowWidth = 1280; //x
const int kWindowHeight = 720; //y

/*********************************
    定数の宣言ここまで
*********************************/

/*********************************
	構造体宣言ここから
*********************************/

typedef struct Point {
	float x;
	float y;
};

typedef struct Ball {

	Point translate;
	float radius;
	Point startPos;
	Point endPos;

	float t;
	float easeT;
};

/*********************************
	構造体宣言ここまで
*********************************/

/*********************************
	関数宣言ここから
*********************************/

void ConstantLinear(Ball& ball) {

	if (ball.t < 1.0f) {
		ball.t += 0.01f;
	}
	else {
		ball.t = 1.0f;
	}

	ball.translate.x = (1.0f - ball.t) * ball.startPos.x + ball.t * ball.endPos.x;

}

void EaseInOut(Ball& ball) {

	if (ball.t < 1.0f) {
		ball.t += 0.01f;
	}
	else {
		ball.t = 1.0f;
	}
	ball.easeT = -(cosf(M_PI * ball.t) - 1.0f) / 2.0f;

	ball.translate.x = (1.0f - ball.easeT) * ball.startPos.x + ball.easeT * ball.endPos.x;
	
}

void EaseIn(Ball& ball) {

	if (ball.t < 1.0f) {
		ball.t += 0.01f;
	}
	else {
		ball.t = 1.0f;
	}
	ball.easeT = ball.t * ball.t;

	ball.translate.x = (1.0f - ball.easeT) * ball.startPos.x + ball.easeT * ball.endPos.x;

}

void EaseOut(Ball& ball) {

	if (ball.t < 1.0f) {
		ball.t += 0.01f;
	}
	else {
		ball.t = 1.0f;
	}
	ball.easeT = 1.0f - powf(1.0f - ball.t, 3.0f);

	ball.translate.x = (1.0f - ball.easeT) * ball.startPos.x + ball.easeT * ball.endPos.x;

}

/*********************************
	関数宣言ここまで
*********************************/

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWinodowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	/*********************************
		変数宣言ここから
	*********************************/

	Ball ball[4];

	for (int i = 0; i < 4; i++) {
		ball[i] = {
			{50.0f, (100.0f + (i * 150.0f))},
			50.0f,
			{50.0f, 50.0f + (i * 100.0f)},
			{1230.0f, 50.0f + (i * 100.0f)},

			0.0f,
			0.0f
		};
	}

	/*********************************
		変数宣言ここまで
	*********************************/

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		/*********************************
			更新処理ここから
		*********************************/

		ConstantLinear(ball[0]);
		EaseInOut(ball[1]);
		EaseIn(ball[2]);
		EaseOut(ball[3]);

		/*********************************
			更新処理ここまで
		*********************************/

		/*********************************
			描画処理ここから
		*********************************/

		Novice::DrawBox(
			0, 0,
			kWinodowWidth, kWindowHeight,
			0.0f,
			BLACK,
			kFillModeSolid
		);

		for (int i = 0; i < 4; i++) {
			Novice::DrawEllipse(
				ball[i].translate.x,
				ball[i].translate.y,

				ball[i].radius,
				ball[i].radius,

				0.0f,

				RED,
				kFillModeSolid
			);

			/*Novice::DrawLine(
				ball[i].translate.x - ball[i].radius * 2,
				ball[i].translate.y - ball[i].radius * 2,

				ball[i].translate.x - ball[i].radius * 2,
				ball[i].translate.y + ball[i].radius * 2,

				WHITE
			);*/

		}

		Novice::ScreenPrintf(30, 25, "Normal");
		Novice::ScreenPrintf(30, 175, "EaseInOut");
		Novice::ScreenPrintf(30, 325, "EaseIn");
		Novice::ScreenPrintf(30, 475, "EaseOut");

		/*********************************
			描画処理ここまで
		*********************************/

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
