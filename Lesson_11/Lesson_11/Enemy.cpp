#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(CVector3 pos, CQuaternion rot, Player* player) :
	m_position(pos),
	m_rotation(rot),
	m_player(player)
{
	m_model.Init(L"Assets/modelData/enemy.cmo");
}
Enemy::~Enemy()
{
}
void Enemy::Update()
{
	//毎フレームちょっとづつ回す。
	CQuaternion addRot;
	//Y軸周りに0.01(ラジアン単位)回転するクォータニオンを作成する。
	addRot.SetRotation(CVector3::AxisY(), 0.01f);
	//エネミーの回転にaddRotを加算する。
	m_rotation.Multiply(addRot);

	//Hands-On 1 エネミーの視野角をプログラミングしてみる。



	//
	//ワールド行列を求める。
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 3.0f, 3.0f, 3.0f });
}
void Enemy::Draw()
{
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
}
