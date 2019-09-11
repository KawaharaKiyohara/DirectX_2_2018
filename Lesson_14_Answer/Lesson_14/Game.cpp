#include "stdafx.h"
#include "Game.h"



Game::Game()
{

	m_sprite.Init(L"Assets/sprite/title.dds", 200, 200);
}


Game::~Game()
{

}

void Game::Update()
{
	m_sprite.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
}

void Game::Draw()
{
	CMatrix mView;
	CMatrix mProj;
	mView.MakeLookAt(
		{0, 0, 1},
		{0, 0, 0},
		{0,1,0}
	);
	mProj.MakeOrthoProjectionMatrix(1280, 720, 0.1, 100);
	m_sprite.Draw(mView, mProj);
}
