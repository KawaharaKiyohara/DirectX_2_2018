#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "Bullet.h"

Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);

	//tka�t�@�C���̓ǂݍ��݁B
	m_animationClips[0].Load(L"Assets/animData/walk.tka");
	m_animationClips[0].SetLoopFlag(true);

	m_animationClips[1].Load(L"Assets/animData/run.tka");
	m_animationClips[1].SetLoopFlag(true);
	//�A�j���[�V�����̏������B
	m_animation.Init(
		m_model,			//�A�j���[�V�����𗬂��X�L�����f���B
							//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
		m_animationClips,	//�A�j���[�V�����N���b�v�̔z��B
		2					//�A�j���[�V�����N���b�v�̐��B
	);

	m_position.y = 100.0f;
	m_charaCon.Init(10.0f, 50.0f, m_position);
}


Player::~Player()
{
}

void Player::Update()
{
	//���K�ۑ�@B�{�^���������Ēe�������Ă݂悤�B
	//�e�ۂ̃C���X�^���X�͉��L�̃R�[�h���Ăяo���ƍ�邱�Ƃ��ł���B
	//
	//	Bullet* bullet = g_game->GetBulletManager().NewBullet();
	//
	//Bullet�N���X�̎����͎����œǂ�Œ��ׂ悤�B
	//�܂��A�v���C���[�̉�]�s��̓X�L�����f���������Ă��ĉ��L�̃R�[�h�Ŏ擾�ł���B�B
	//
	//	CMatrix rotMatrix = m_model.GetRotationMatrix();
	//
	
	if (g_pad[0].IsTrigger(enButtonA) == true
		&& m_charaCon.IsOnGround() == true
		) {
		m_moveSpeed.y += 500.0f;
	}

	//m_moveSpeed�̓v���C���[�N���X�̃����o�ϐ��B
	//XZ���ʂ̈ړ����x�̓p�b�h�̓��͂�����������Ă���B
	m_moveSpeed.x = g_pad[0].GetLStickXF() * -300.0f;
	m_moveSpeed.z = g_pad[0].GetLStickYF() * -300.0f;
	//Y�����̈ړ����x�͏d�͉������s���B
	m_moveSpeed.y -= 980.0f * (1.0f / 60.0f);
	//�L�����N�^�[�R���g���[���[�ɂP�t���[���̌o�ߎ���:�b(������)�A���ԃx�[�X�̈ړ����x(������)��n���Ă���B
	//Execute�֐��̒��ōs���Ă���v�Z�͉��L�̂悤�Ȃ��́B
	//
	// CVector3 addPos = moveSpeed * ( 1.0f / 60.0f ); //�P�t���[���ňړ�����ʂ��v�Z����B
	// position += addPos;  //1�t���[���̈ړ��ʂ����W�ɉ��Z����B������I�C���[�ϕ��Ƃ����B
	//
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);

	//�������ς���B
	if (fabsf(m_moveSpeed.x) > 0.1f || fabsf(m_moveSpeed.z) > 0.1f) {
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(m_moveSpeed.x, m_moveSpeed.z));
	}
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_animation.Update(1.0f / 30.0f);
}
void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}