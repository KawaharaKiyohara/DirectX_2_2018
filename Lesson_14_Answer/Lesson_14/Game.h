#pragma once

#include "Graphics/Sprite.h"


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
	void Game::Update();
	void Game::Draw();
private:
	Sprite m_sprite;								//スプライト。
};


