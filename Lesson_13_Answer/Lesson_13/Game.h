#pragma once

#include "IScene.h"
#include "Player.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "BulletManager.h"

//�����͑O���錾�ł悢�I
struct PathPoint;
class Enemy;

//�Q�[���N���X�B
class Game : public IScene
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
	void Update() override;
	/*!
	* @brief	�`��B
	*/
	void Draw() override;
	/*!
	* @brief	�p�X���擾�B
	*/
	std::vector< PathPoint* >& GetPath()
	{
		return m_path;
	}
	/*!
	* @brief	�e�ۃ}�l�[�W�����擾�B
	*/
	BulletManager& GetBulletManager()
	{
		return m_bulletManager;
	}
private:
	Player m_player;						//�v���C���[
	GameCamera m_gameCamera;				//�Q�[���J�����B
	Level m_level;							//���x�����������B
	std::vector< Enemy* > m_enemyList;		//�G�l�~�[�̃��X�g�B
	std::vector< PathPoint* > m_path;		//�p�X�B
	BulletManager m_bulletManager;			//�e�ۂȃ}�l�[�W���B
};

//�O���[�o���ȃA�N�Z�X�|�C���g���O���[�o���ϐ��Ƃ��Ē񋟂���B
extern Game* g_game;


