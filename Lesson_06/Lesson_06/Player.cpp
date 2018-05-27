#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");

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
}


Player::~Player()
{
}

void Player::Update()
{
	
	//�@A�{�^���������ꂽ�瑖��A�j���[�V�������Đ�����B
	if (g_pad[0].IsTrigger(enButtonA)) {
		//����A�j���[�V�������Đ�����B
		m_animation.Play(1);
	}
	//B�{�^���������ꂽ������A�j���[�V�������Đ�����B
	if (g_pad[0].IsTrigger(enButtonB)) {
		//�����A�j���[�V�������Đ�����B
		m_animation.Play(0);
	}

	//X�{�^���������ꂽ�瑖��A�j���[�V�������ԕt���ōĐ�����B
	if (g_pad[0].IsTrigger(enButtonX)) {
		//����A�j���[�V�������Đ�����B
		m_animation.Play(1, 0.3f);
	}
	//Y�{�^���������ꂽ������A�j���[�V�������ԕt���ōĐ�����B
	if (g_pad[0].IsTrigger(enButtonY)) {
		//�����A�j���[�V�������Đ�����B
		m_animation.Play(0, 0.3f);
	}
	//��{�^���������ꂽ��AUnity������Y�������̊g�嗦�𑝂₷�B
	if (g_pad[0].IsPress(enButtonUp)) {
		m_scale.y += 0.01f;
	}
	//���{�^���������ꂽ��AUnity������Y�������̊g�嗦�����炷�B
	if (g_pad[0].IsPress(enButtonDown)) {
		m_scale.y -= 0.01f;
	}
	//�E�{�^���������ꂽ��AUnity������X�������̊g�嗦�𑝂₷�B
	if (g_pad[0].IsPress(enButtonRight)) {
		m_scale.x += 0.01f;
	}
	//���{�^���������ꂽ��AUnity������X�������̊g�嗦�����炷�B
	if (g_pad[0].IsPress(enButtonLeft)) {
		m_scale.x -= 0.01f;
	}
	//��{�^���������ꂽ��AUnity������Y�������̊g�嗦�𑝂₷�B
	if (g_pad[0].IsPress(enButtonUp)) {
		m_scale.y += 0.01f;
	}
	//���{�^���������ꂽ��AUnity������Y�������̊g�嗦�����炷�B
	if (g_pad[0].IsPress(enButtonLeft)) {
		m_scale.y -= 0.01f;
	}

	//���X�e�B�b�N�̓��͂�Unity�����𓮂����B
	m_position.x += g_pad[0].GetLStickXF() * 2.0f;
	m_position.y += g_pad[0].GetLStickYF() * 2.0f;
	//�E�X�e�B�b�N�̓��͂�Unity�������񂷁B
	CQuaternion qAdd;
	qAdd.SetRotationDeg(CVector3::AxisY(), g_pad[0].GetRStickXF() * 2.0f);
	m_rotation.Multiply(qAdd);	//Y������̉�]�����Z�B

	qAdd.SetRotationDeg(CVector3::AxisX(), g_pad[0].GetRStickYF() * 2.0f);
	m_rotation.Multiply(qAdd);	//X������̉�]�����Z�B


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