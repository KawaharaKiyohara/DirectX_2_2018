#pragma once

#include "Graphics/Sprite.h"


//�Q�[���N���X�B
class Game 
{
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*/
	Game();
	/*!
	* @brief	�f�X�g���N�^
	*/
	~Game();
	void Game::Update();
	void Game::Draw();
private:
	Sprite m_sprite;								//�X�v���C�g�B
};


