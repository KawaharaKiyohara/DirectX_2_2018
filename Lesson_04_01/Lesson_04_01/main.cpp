/*!
 *@brief	�V�F�[�_�[�̃`���[�g���A��00
 */
#include "stdafx.h"
#include "Camera.h"
#include "Ball.h"
#include "Skelton.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��B
//-----------------------------------------------------------------------------

const int				LIGHT_NUM = 4;
D3DXVECTOR4 			g_diffuseLightDirection[LIGHT_NUM];	//���C�g�̕����B
D3DXVECTOR4				g_diffuseLightColor[LIGHT_NUM];		//���C�g�̐F�B
D3DXVECTOR4				g_ambientLight;						//����

Camera camera;				//�J�����B

const int NUM_BALL = 7;
Ball ball[NUM_BALL];	//�{�[���B
Skelton ballSkelton;	//�{�[���̃X�P���g���B

enum EBone {
	eBonePelvis,
	eBoneLeftFoot ,
	eBoneRightFoot ,
	eBoneBody,
	eBoneHead,
	eBoneLeftHand,
	eBoneRightHand,
};
/*!-----------------------------------------------------------------------------
 *@brief	���C�g���X�V�B
 -----------------------------------------------------------------------------*/
void UpdateLight()
{
	g_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	//�f�B�t���[�Y���C�g�B
	g_diffuseLightColor[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

//�����B
g_ambientLight = D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f);
}
//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void Init()
{
	//���C�g���������B
	ZeroMemory(g_diffuseLightDirection, sizeof(g_diffuseLightDirection));
	ZeroMemory(g_diffuseLightColor, sizeof(g_diffuseLightColor));


	//�X�P���g�����\�z�B
	//Lesson 1	�X�P���g���̍\�z�ɂ��Đ�������B
	//���Ձ@���ꂪ���[�g
	Bone bone;
	D3DXQuaternionIdentity(&bone.rotation);
	bone.position.x = 0.0f;
	bone.position.y = 0.0f;
	bone.position.z = 0.0f;
	ballSkelton.AddBone(-1, &bone);
	//����
	bone.position.x = -0.5f;
	bone.position.y = -0.5f;
	bone.position.z = 0.0f;
	ballSkelton.AddBone(0, &bone);
	//�E���B
	bone.position.x = 0.5f;
	bone.position.y = -0.5f;
	bone.position.z = 0.0f;
	ballSkelton.AddBone(0, &bone);
	//����
	bone.position.x = 0.0f;
	bone.position.y = 0.5f;
	bone.position.z = 0.0f;
	ballSkelton.AddBone(0, &bone);
	//��
	bone.position.x = 0.0f;
	bone.position.y = 1.0f;
	bone.position.z = 0.0f;
	ballSkelton.AddBone(3, &bone);
	//����
	bone.position.x = -0.5f;
	bone.position.y = 0.5f;
	bone.position.z = 0.0f;
	ballSkelton.AddBone(3, &bone);
	//�E��
	bone.position.x = 0.5f;
	bone.position.y = 0.5f;
	bone.position.z = 0.0f;
	ballSkelton.AddBone(3, &bone);


	//�{�[�����������B
	for (int i = 0; i < NUM_BALL; i++) {
		ball[i].Init(&ballSkelton, i);
	}
	//�J�����̏������B
	camera.Init();

}
//-----------------------------------------------------------------------------
// Name: �`�揈���B
//-----------------------------------------------------------------------------
VOID Render()
{
	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	g_pd3dDevice->BeginScene();
	//�g����`��B
	for (int i = 0; i < NUM_BALL; i++) {
		ball[i].Render(
			g_pd3dDevice,
			camera.GetViewMatrix(),
			camera.GetProjectionMatrix(),
			g_diffuseLightDirection,
			g_diffuseLightColor,
			g_ambientLight,
			LIGHT_NUM
			);
	}

	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
 *@brief	�X�V�����B
 -----------------------------------------------------------------------------*/
void Update()
{
	//���C�g�̍X�V�B
	UpdateLight();
	//�J�����̍X�V
	camera.Update();
	//Lesson-2 CalcGlobalPose�ɂ��Đ�������B
	//�O���[�o���|�[�Y�̍X�V
	ballSkelton.CalcGlobalPose();
	
	//Hands-On 1 �{�[���𓮂����B
	
	//Hands-On 2 �{�[�����񂷁B
	
}
//-----------------------------------------------------------------------------
//�Q�[�����I������Ƃ��ɌĂ΂�鏈���B
//-----------------------------------------------------------------------------
void Terminate()
{
}
