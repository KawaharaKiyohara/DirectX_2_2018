#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "level/Level.h"
#include "Mikyan.h"


//Mikyan�̃X�}�[�g�|�C���^�̕ʖ���`�B
using MikyanPtr = std::unique_ptr< Mikyan >;

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

	
	std::vector< MikyanPtr > mikyanArray;
	//���x�����������B
	Level level;
	level.Init(L"Assets/level/stage_00.tkl", nullptr);

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
		//�v���C���[�̕`��B
		player.Draw();
		//���x����`��B
		level.Draw();
		//�݂������X�V���ĕ`��B
		for (auto& m : mikyanArray) {
			m->Update();
			m->Draw();
		}
		//�J�����̍X�V�B
		g_camera3D.Update();
		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}