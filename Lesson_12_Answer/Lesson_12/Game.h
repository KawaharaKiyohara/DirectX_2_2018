#pragma once

//これらは前方宣言でいい。
//詳しく知りたいならEffective C++を読むように。
#include "Player.h"
#include "GameCamera.h"
#include "Level/Level.h"

class Enemy;
struct PathPoint;


//ゲームクラス。
class Game
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
	void Update();
	/*!
	* @brief	描画。
	*/
	void Draw();
	/*!
	* @brief	パスを取得。
	*/
	std::vector< PathPoint* >& GetPath()
	{
		return path;
	}
private:
	//プレイヤー
	Player player;
	//ゲームカメラ。
	GameCamera gameCamera;
	//レベルを初期化。
	Level level;
	std::vector< Enemy* > enemyList;		//エネミーのリスト。
	std::vector< PathPoint* > path;		//パス。
};

//グローバルなアクセスポイントをグローバル変数として提供する。
extern Game* g_game;


