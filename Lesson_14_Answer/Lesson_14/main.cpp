#include "stdafx.h"
#include "system/system.h"
#include <algorithm>
#include "Game.h"

Game* g_game;


///////////////////////////////////////////////////////////////////
//�Q�[���̍X�V�����B
//���W�̍X�V�Ƃ��̏����͂����ŌĂяo���Ƃ悢�����H
///////////////////////////////////////////////////////////////////
void UpdateGame()
{
	//�Q�[���p�b�h�̍X�V�B	
	for (auto& pad : g_pad) {
		pad.Update();
	}

	g_game->Update();

	//�����G���W���̍X�V�B
	g_physics.Update();
}
///////////////////////////////////////////////////////////////////
// �Q�[���̕`�揈���B
// �`��ƍX�V�͕����Ă��ق����ǂ������H
///////////////////////////////////////////////////////////////////
void RenderGame()
{
	//�`��J�n�B
	g_graphicsEngine->BegineRender();

	g_game->Draw();

	//�`��I���B
	g_graphicsEngine->EndRender();
}

///////////////////////////////////////////////////////////////////
// �Q�[���̏I�������B
///////////////////////////////////////////////////////////////////
void TermnateGame()
{
	
	
}
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���G���W���̏������B
	InitGameEngine(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	
	g_game = new Game;

	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�Q�[���̍X�V�B
		UpdateGame();
		//�Q�[���̕`�揈���B
		RenderGame();
	}
	//�Q�[���̏I������
	TermnateGame();
}