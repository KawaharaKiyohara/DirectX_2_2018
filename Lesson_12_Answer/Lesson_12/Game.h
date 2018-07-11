#pragma once

//�����͑O���錾�ł����B
//�ڂ����m�肽���Ȃ�Effective C++��ǂނ悤�ɁB
class Player;
class GameCamera;
class Level;
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
	Player * player = nullptr;
	//�Q�[���J�����B
	GameCamera* gameCamera = nullptr;
	//���x�����������B
	Level* level = nullptr;;
	std::vector< Enemy* > enemyList;		//�G�l�~�[�̃��X�g�B
	std::vector< PathPoint* > path;		//�p�X�B
};

//�O���[�o���ȃA�N�Z�X�|�C���g���O���[�o���ϐ��Ƃ��Ē񋟂���B
extern Game* g_game;


