#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3D�J�����B

void Camera::Update()
{
	//�r���[�s����v�Z�B
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	if (m_calcProjectionMatrixFunc == enCalcProjectionMatrixFunc_Perspective) {
		//�������e�s��B
		//�v���W�F�N�V�����s����v�Z�B
		m_projMatrix.MakeProjectionMatrix(
			m_viewAngle,					//��p�B
			FRAME_BUFFER_W / FRAME_BUFFER_H,	//�A�X�y�N�g��B
			m_near,
			m_far
		);
	}
	else if (m_calcProjectionMatrixFunc == enCalcProjectionMatrixFunc_Ortho) {
		//���s���e�s��B
		//�v���W�F�N�V�����s����v�Z�B
		m_projMatrix.MakeOrthoProjectionMatrix(
			m_viewVolumeWidth,		//�r���[�{�����[���̕��B
			m_viewVolumeHeight,		//�r���[�{�����[���̍���
			m_near,
			m_far
		);
	}
}