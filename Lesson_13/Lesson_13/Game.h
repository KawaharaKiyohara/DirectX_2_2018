#pragma once

#include "IScene.h"
#include "Player.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "BulletManager.h"

//これらは前方宣言でよい！
struct PathPoint;
class Enemy;

//ゲームクラス。
class Game : public IScene
{
public:
	/*!
	* @brief	コンストラクタ。
	*/
	Game();
	/*!
	* @brief	デストラクタ
	*/
	~Game();
	/*!
	* @brief	更新。
	*/
	void Update() override;
	/*!
	* @brief	描画。
	*/
	void Draw() override;
	/*!
	* @brief	パスを取得。
	*/
	std::vector< PathPoint* >& GetPath()
	{
		return m_path;
	}
	/*!
	* @brief	弾丸マネージャを取得。
	*/
	BulletManager& GetBulletManager()
	{
		return m_bulletManager;
	}
private:
	Player m_player;						//プレイヤー
	GameCamera m_gameCamera;				//ゲームカメラ。
	Level m_level;							//レベルを初期化。
	std::vector< Enemy* > m_enemyList;		//エネミーのリスト。
	std::vector< PathPoint* > m_path;		//パス。
	BulletManager m_bulletManager;			//弾丸なマネージャ。
};

//グローバルなアクセスポイントをグローバル変数として提供する。
extern Game* g_game;


