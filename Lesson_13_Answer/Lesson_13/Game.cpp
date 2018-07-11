#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "Path.h"


//グローバルなアクセスポイントをグローバル変数として提供する。
Game* g_game = nullptr;

Game::Game()
{
	g_game = this;
	//パスデータをリザーブ。
	m_path.reserve(512);	//512もあれば十分やろう。
						//レベルを構築する。
	
	m_level.Init(L"Assets/level/stage_00.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualName(L"unityChan") == true) {
			//Unityちゃん。
			
			m_player.SetPosition(objData.position);
			return true;
		}
		else if (objData.EqualName(L"enemy") == true) {
			//エネミー！！！
			auto enemy = new Enemy(objData.position, objData.rotation, &m_player);
			m_enemyList.push_back(enemy);
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
			m_path.push_back(pathPoint);
			return true;
		}
		//これら以外は静的オブジェクト。
		return false;
	});

	//パスを番号順でソートする。
	std::sort(m_path.begin(), m_path.end(), [](PathPoint* lp, PathPoint* rp) {
		//右側のほうが小さい。
		return lp->pointNo < rp->pointNo;
	});
	m_gameCamera.SetPlayer(&m_player);
	
}


Game::~Game()
{
	g_game = nullptr;
	//動的に確保したインスタンスを破棄。
	for (auto& enemy : m_enemyList) {
		delete enemy;
	}
	for (auto& pt : m_path) {
		delete pt;
	}
}

void Game::Update()
{
	//プレイヤーの更新。
	m_player.Update();
	m_gameCamera.Update();
	//Enemyを更新。
	for (auto& enemy : m_enemyList) {
		enemy->Update();
	}
	//弾丸を更新。
	m_bulletManager.Update();
}

void Game::Draw()
{
	//プレイヤーの描画。
	m_player.Draw();
	//レベルを描画。
	m_level.Draw();
	//エネミーを描画。
	for (auto& enemy : m_enemyList) {
		enemy->Draw();
	}
	m_bulletManager.Draw();
}
