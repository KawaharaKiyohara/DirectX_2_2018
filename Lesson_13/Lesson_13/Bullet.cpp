#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
	m_model.Init(L"Assets/modelData/bullet.cmo");
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	m_pos += m_moveSpeed;
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}
void Bullet::Draw()
{
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
}