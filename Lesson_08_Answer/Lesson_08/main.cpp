#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "Background.h"
#include "Mikyna.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 300.0f, 800.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	//プレイヤー
	Player player;
	//プレイヤーの初期化。
	player.SetPosition({ 30.0f, 0.0f, 0.0f });

	//背景。
	Background bg;

	//みきゃん。
	Mikyna mikyan;
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();

		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}

		//物理エンジンの更新。
		g_physics.Update();
		//プレイヤーの更新。
		player.Update();
		//プレイヤーの描画。
		player.Draw();
		//背景を描画。
		bg.Draw();
		//みきゃんを描画。
		mikyan.Draw();
		//カメラの更新。
		g_camera3D.Update();
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}