#include "stdafx.h"
#include "Mikyna.h"


Mikyna::Mikyna()
{
	m_model.Init(L"Assets/modelData/mikyan.cmo");
	m_model.UpdateWorldMatrix({200.0f, 0.0f, 0.0f}, CQuaternion::Identity(), CVector3::One());
	m_phyStaticObject.CreateMeshObject(m_model, { 200.0f, 0.0f, 0.0f }, CQuaternion::Identity());
}
Mikyna::~Mikyna()
{
}
void Mikyna::Draw()
{
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
}