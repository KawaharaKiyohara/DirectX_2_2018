#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "Path.h"

Game::Game()
{
	//�p�X�f�[�^�����U�[�u�B
	path.reserve(512);	//512������Ώ\����낤�B
						//���x�����\�z����B
	player = new Player;
	level = new Level;
	level->Init(L"Assets/level/stage_00.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualName(L"unityChan") == true) {
			//Unity�����B
			
			player->SetPosition(objData.position);
			return true;
		}
		else if (objData.EqualName(L"enemy") == true) {
			//�G�l�~�[�I�I�I
			auto enemy = new Enemy(objData.position, objData.rotation, player);
			enemyList.push_back(enemy);
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
			path.push_back(pathPoint);
			return true;
		}
		//�����ȊO�͐ÓI�I�u�W�F�N�g�B
		return false;
	});

	//�p�X��ԍ����Ń\�[�g����B
	std::sort(path.begin(), path.end(), [](PathPoint* lp, PathPoint* rp) {
		//�E���̂ق����������B
		return lp->pointNo < rp->pointNo;
	});
	gameCamera = new GameCamera();
	gameCamera->SetPlayer(player);
	
}


Game::~Game()
{
	//���I�Ɋm�ۂ����C���X�^���X��j���B
	delete player;
	delete level;
	delete gameCamera;
	for (auto& enemy : enemyList) {
		delete enemy;
	}
	for (auto& pt : path) {
		delete pt;
	}
}

void Game::Update()
{
	//�v���C���[�̍X�V�B
	player->Update();
	gameCamera->Update();
	//Enemy���X�V�B
	for (auto& enemy : enemyList) {
		enemy->Update();
	}
}

void Game::Draw()
{
	//�v���C���[�̕`��B
	player->Draw();
	//���x����`��B
	level->Draw();
	//Coin��`��B
	for (auto& enemy : enemyList) {
		enemy->Draw();
	}
}
