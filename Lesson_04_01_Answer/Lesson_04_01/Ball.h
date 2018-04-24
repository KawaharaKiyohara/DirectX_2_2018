#pragma once

#include "Model.h"

class Skelton;
class Ball {
public:
	//コンストラクタ。
	Ball();
	//初期化。
	//skelton	スケルトン
	//jointNo	ボーン番号。
	void Init(Skelton* skelton, int boneNo);
	//描画関数
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
	Skelton*	skelton;	//スケルトン、
	Model		model;		//モデル。
	int			boneNo;		//ボーンの番号。
};