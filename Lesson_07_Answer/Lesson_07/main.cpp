#include "stdafx.h"
#include "system/system.h"
#include "Player.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	//�r���[�{�����[���̕��ƍ������w�肷��B
	float aspect = 1280.0f / 720.0f;
	g_camera3D.SetViewVolumeHeight(300.0f);
	g_camera3D.SetViewVolumeWidth(300.0f * aspect);
	//�v���W�F�N�V�����s��̌v�Z���@���s���e�ɂ���B
	g_camera3D.SetCalcProjectionMatrixFunc(Camera::enCalcProjectionMatrixFunc_Ortho);

	Player player[2];	//�v���C���[�̔z��B
	//�v���C���[�P�̏������B
	player[0].SetPosition({ 30.0f, 0.0f, 0.0f });
	player[0].SetPadNo(0); //�p�b�h�ԍ�0���g���B

	//�v���C���[2�̏������B
	player[1].SetPosition({ -30.0f, 0.0f, 0.0f });
	player[1].SetPadNo(1); //�p�b�h�ԍ�1���g���B
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();

		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}

		//�v���C���[�̍X�V�B
		for (auto& pl : player) {
			pl.Update();
		}
		
		g_camera3D.Update();

		//�v���C���[�̕`��B
		for (auto& pl : player) {
			pl.Draw();
		}

		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}