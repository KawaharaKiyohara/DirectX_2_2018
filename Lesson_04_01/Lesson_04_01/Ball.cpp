#include "stdafx.h"
#include "Ball.h"
#include "Skelton.h"

//�R���X�g���N�^�B
Ball::Ball()
{
	skelton = NULL;
}
//�������B
void Ball::Init(Skelton* skelton, int boneNo)
{
	model.Init(g_pd3dDevice, "ball.x");
	this->skelton = skelton;
	this->boneNo = boneNo;
}
//�`��B
void Ball::Render(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight
	)
{
	const D3DXMATRIX* mWorld;
	//�Ή����鍜�̍s����擾�B
	mWorld = skelton->GetWorldMatrix(boneNo);
	model.Render(pd3dDevice, *mWorld, *mWorld, viewMatrix, projMatrix, diffuseLightDirection, diffuseLightColor, ambientLight, numDiffuseLight);

}