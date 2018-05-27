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
	
	Player player; //プレイヤー。
	
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();

		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}

		//実習１　カメラを回転させてみよう。
		CQuaternion qRot;
		CVector3 camPos = g_camera3D.GetPosition();
		CVector3 camTar = g_camera3D.GetTarget();
		//注視点から視点に向かって伸びるベクトルtoTargetを計算する。
		CVector3 toPos = camPos - camTar;
		//Y軸周りに0.2°回転する回転クォータニオンを作成。
		qRot.SetRotation(CVector3::AxisY(), 0.1f);
		//toTargetをY軸周りに0.2°回す。
		qRot.Multiply(toPos);
		//新しい視点を求める。
		camPos = camTar + toPos;
		g_camera3D.SetPosition(camPos);

		player.Update();
		g_camera3D.Update();

		player.Draw();

		//描画終了。
		g_graphicsEngine->EndRender();
	}
}