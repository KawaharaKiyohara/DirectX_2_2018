#pragma once

//�����͑O���錾�ł����B
//�ڂ����m�肽���Ȃ�Effective C++��ǂނ悤�ɁB
#include "Player.h"
#include "GameCamera.h"
#include "Level/Level.h"

class Enemy;
struct PathPoint;


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
	/*!
	* @brief	�X�V�B
	*/
	void Update();
	/*!
	* @brief	�`��B
	*/
	void Draw();
	/*!
	* @brief	�p�X���擾�B
	*/
	std::vector< PathPoint* >& GetPath()
	{
		return path;
	}
private:
	//�v���C���[
	Player player;
	//�Q�[���J�����B
	GameCamera gameCamera;
	//���x�����������B
	Level level;
	std::vector< Enemy* > enemyList;		//�G�l�~�[�̃��X�g�B
	std::vector< PathPoint* > path;		//�p�X�B
};

//�O���[�o���ȃA�N�Z�X�|�C���g���O���[�o���ϐ��Ƃ��Ē񋟂���B
extern Game* g_game;


