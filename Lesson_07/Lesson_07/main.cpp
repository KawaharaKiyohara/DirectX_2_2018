#include "stdafx.h"
#include "system/system.h"
#include "Player.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	
	Player player[2];	//プレイヤーの配列。
	//プレイヤー１の初期化。
	player[0].SetPosition({ 30.0f, 0.0f, 0.0f });
	player[0].SetPadNo(0); //パッド番号0を使う。

	//プレイヤー2の初期化。
	player[1].SetPosition({ -30.0f, 0.0f, 0.0f });
	player[1].SetPadNo(1); //パッド番号1を使う。
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();

		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}

		//プレイヤーの更新。
		for (auto& pl : player) {
			pl.Update();
		}
		
		g_camera3D.Update();

		//プレイヤーの描画。
		for (auto& pl : player) {
			pl.Draw();
		}

		//描画終了。
		g_graphicsEngine->EndRender();
	}
}