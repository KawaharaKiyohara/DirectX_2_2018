#pragma once

//これらは前方宣言でいい。
//詳しく知りたいならEffective C++を読むように。
class Player;
class GameCamera;
class Level;
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
	Player * player = nullptr;
	//ゲームカメラ。
	GameCamera* gameCamera = nullptr;
	//レベルを初期化。
	Level* level = nullptr;;
	std::vector< Enemy* > enemyList;		//エネミーのリスト。
	std::vector< PathPoint* > path;		//パス。
};

//グローバルなアクセスポイントをグローバル変数として提供する。
extern Game* g_game;


