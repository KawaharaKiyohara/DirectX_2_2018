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
	//���t���[��������ƂÂ񂷁B
	CQuaternion addRot;
	//Y�������0.01(���W�A���P��)��]����N�H�[�^�j�I�����쐬����B
	addRot.SetRotation(CVector3::AxisY(), 0.01f);
	//�G�l�~�[�̉�]��addRot�����Z����B
	m_rotation.Multiply(addRot);

	//Hands-On 1 �G�l�~�[�̎���p���v���O���~���O���Ă݂�B



	//
	//���[���h�s������߂�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 3.0f, 3.0f, 3.0f });
}
void Enemy::Draw()
{
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
}
