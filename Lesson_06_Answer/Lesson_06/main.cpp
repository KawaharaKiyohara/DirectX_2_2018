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
	
	Player player; //�v���C���[�B
	
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();

		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}

		//���K�P�@�J��������]�����Ă݂悤�B
		CQuaternion qRot;
		CVector3 camPos = g_camera3D.GetPosition();
		CVector3 camTar = g_camera3D.GetTarget();
		//�����_���王�_�Ɍ������ĐL�т�x�N�g��toTarget���v�Z����B
		CVector3 toPos = camPos - camTar;
		//Y�������0.2����]�����]�N�H�[�^�j�I�����쐬�B
		qRot.SetRotation(CVector3::AxisY(), 0.1f);
		//toTarget��Y�������0.2���񂷁B
		qRot.Multiply(toPos);
		//�V�������_�����߂�B
		camPos = camTar + toPos;
		g_camera3D.SetPosition(camPos);

		player.Update();
		g_camera3D.Update();

		player.Draw();

		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}