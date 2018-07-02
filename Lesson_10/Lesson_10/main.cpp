#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "level/Level.h"
#include "Star.h"
#include <algorithm>

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

	//Starのリスト。
	std::vector< std::unique_ptr< Star > > starList;
	//レベルを初期化。
	Level level;
	level.Init(L"Assets/level/stage_00.tkl", [&](LevelObjectData& objData)->bool {
		if (wcscmp(objData.name, L"star") == 0) {
			//Star。
			auto coin = std::make_unique<Star>( player, objData.position);
			starList.push_back(std::move(coin));
			//フックした。
			return true;
		}
		return false;
	});

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
		//Starを更新。
		for (auto& star : starList) {
			star->Update();
		}
		//Coinの削除処理。
		//削除判定用の匿名関数を定義する。
		auto ifDelFunc = [](auto& coin) ->bool {
			return coin->IsDead();
		};
		starList.erase(
			std::remove_if(starList.begin(), starList.end(), ifDelFunc),
			starList.end()
		);
		//プレイヤーの描画。
		player.Draw();
		//レベルを描画。
		level.Draw();
		//Coinを描画。
		for (auto& star : starList) {
			star->Draw();
		}
		//カメラの更新。
		g_camera3D.Update();
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}