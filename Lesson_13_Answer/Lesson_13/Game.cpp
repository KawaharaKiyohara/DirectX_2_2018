#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "Path.h"


//�O���[�o���ȃA�N�Z�X�|�C���g���O���[�o���ϐ��Ƃ��Ē񋟂���B
Game* g_game = nullptr;

Game::Game()
{
	g_game = this;
	//�p�X�f�[�^�����U�[�u�B
	m_path.reserve(512);	//512������Ώ\����낤�B
						//���x�����\�z����B
	
	m_level.Init(L"Assets/level/stage_00.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualName(L"unityChan") == true) {
			//Unity�����B
			
			m_player.SetPosition(objData.position);
			return true;
		}
		else if (objData.EqualName(L"enemy") == true) {
			//�G�l�~�[�I�I�I
			auto enemy = new Enemy(objData.position, objData.rotation, &m_player);
			m_enemyList.push_back(enemy);
			return true;
		}
		else if (objData.ForwardMatchName(L"Path_") == true) {
			//�p�X�f�[�^�B
			//�|�C���g�ԍ��𒊏o����B
			//6�����ڂ��琔���������Ă���B
			//�����������̓q���[�}���G���[�����o����R�[�h�������Ɨǂ��B
			int pointNo = _wtoi(&objData.name[5]);
			auto pathPoint = new PathPoint;
			pathPoint->position = objData.position;
			pathPoint->pointNo = pointNo;
			m_path.push_back(pathPoint);
			return true;
		}
		//�����ȊO�͐ÓI�I�u�W�F�N�g�B
		return false;
	});

	//�p�X��ԍ����Ń\�[�g����B
	std::sort(m_path.begin(), m_path.end(), [](PathPoint* lp, PathPoint* rp) {
		//�E���̂ق����������B
		return lp->pointNo < rp->pointNo;
	});
	m_gameCamera.SetPlayer(&m_player);
	
}


Game::~Game()
{
	g_game = nullptr;
	//���I�Ɋm�ۂ����C���X�^���X��j���B
	for (auto& enemy : m_enemyList) {
		delete enemy;
	}
	for (auto& pt : m_path) {
		delete pt;
	}
}

void Game::Update()
{
	//�v���C���[�̍X�V�B
	m_player.Update();
	m_gameCamera.Update();
	//Enemy���X�V�B
	for (auto& enemy : m_enemyList) {
		enemy->Update();
	}
	//�e�ۂ��X�V�B
	m_bulletManager.Update();
}

void Game::Draw()
{
	//�v���C���[�̕`��B
	m_player.Draw();
	//���x����`��B
	m_level.Draw();
	//�G�l�~�[��`��B
	for (auto& enemy : m_enemyList) {
		enemy->Draw();
	}
	m_bulletManager.Draw();
}
