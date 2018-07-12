#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "Path.h"

Game::Game()
{
	//パスデータをリザーブ。
	path.reserve(512);	//512もあれば十分やろう。
						//レベルを構築する。
	level.Init(L"Assets/level/stage_00.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualName(L"unityChan") == true) {
			//Unityちゃん。
			
			player.SetPosition(objData.position);
			return true;
		}
		else if (objData.EqualName(L"enemy") == true) {
			//エネミー！！！
			auto enemy = new Enemy(objData.position, objData.rotation, &player);
			enemyList.push_back(enemy);
			return true;
		}
		else if (objData.ForwardMatchName(L"Path_") == true) {
			//パスデータ。
			//ポイント番号を抽出する。
			//6文字目から数字が入っている。
			//こういう時はヒューマンエラーを検出するコードを書くと良い。
			int pointNo = _wtoi(&objData.name[5]);
			auto pathPoint = new PathPoint;
			pathPoint->position = objData.position;
			pathPoint->pointNo = pointNo;
			path.push_back(pathPoint);
			return true;
		}
		//これら以外は静的オブジェクト。
		return false;
	});

	//パスを番号順でソートする。
	std::sort(path.begin(), path.end(), [](PathPoint* lp, PathPoint* rp) {
		//右側のほうが小さい。
		return lp->pointNo < rp->pointNo;
	});
	gameCamera.SetPlayer(&player);
	
}


Game::~Game()
{
	//動的に確保したインスタンスを破棄。
	for (auto& enemy : enemyList) {
		delete enemy;
	}
	for (auto& pt : path) {
		delete pt;
	}
}

void Game::Update()
{
	//プレイヤーの更新。
	player.Update();
	gameCamera.Update();
	//Enemyを更新。
	for (auto& enemy : enemyList) {
		enemy->Update();
	}
}

void Game::Draw()
{
	//プレイヤーの描画。
	player.Draw();
	//レベルを描画。
	level.Draw();
	//Coinを描画。
	for (auto& enemy : enemyList) {
		enemy->Draw();
	}
}
