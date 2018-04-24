#pragma once

#include "Model.h"

class Skelton;
class Ball {
public:
	//�R���X�g���N�^�B
	Ball();
	//�������B
	//skelton	�X�P���g��
	//jointNo	�{�[���ԍ��B
	void Init(Skelton* skelton, int boneNo);
	//�`��֐�
	void Render(
		LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight
		);
private:
	Skelton*	skelton;	//�X�P���g���A
	Model		model;		//���f���B
	int			boneNo;		//�{�[���̔ԍ��B
};