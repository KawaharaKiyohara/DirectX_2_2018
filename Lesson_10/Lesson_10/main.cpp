#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "level/Level.h"
#include "Star.h"
#include <algorithm>

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 300.0f, 800.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	//�v���C���[
	Player player;
	//�v���C���[�̏������B
	player.SetPosition({ 30.0f, 0.0f, 0.0f });

	//Star�̃��X�g�B
	std::vector< std::unique_ptr< Star > > starList;
	//���x�����������B
	Level level;
	level.Init(L"Assets/level/stage_00.tkl", [&](LevelObjectData& objData)->bool {
		if (wcscmp(objData.name, L"star") == 0) {
			//Star�B
			auto coin = std::make_unique<Star>( player, objData.position);
			starList.push_back(std::move(coin));
			//�t�b�N�����B
			return true;
		}
		return false;
	});

	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();
		//�v���C���[�̍X�V�B
		player.Update();
		//Star���X�V�B
		for (auto& star : starList) {
			star->Update();
		}
		//Coin�̍폜�����B
		//�폜����p�̓����֐����`����B
		auto ifDelFunc = [](auto& coin) ->bool {
			return coin->IsDead();
		};
		starList.erase(
			std::remove_if(starList.begin(), starList.end(), ifDelFunc),
			starList.end()
		);
		//�v���C���[�̕`��B
		player.Draw();
		//���x����`��B
		level.Draw();
		//Coin��`��B
		for (auto& star : starList) {
			star->Draw();
		}
		//�J�����̍X�V�B
		g_camera3D.Update();
		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}