#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3Dカメラ。

void Camera::Update()
{
	//ビュー行列を計算。
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	if (m_calcProjectionMatrixFunc == enCalcProjectionMatrixFunc_Perspective) {
		//透視投影行列。
		//プロジェクション行列を計算。
		m_projMatrix.MakeProjectionMatrix(
			m_viewAngle,					//画角。
			FRAME_BUFFER_W / FRAME_BUFFER_H,	//アスペクト比。
			m_near,
			m_far
		);
	}
	else if (m_calcProjectionMatrixFunc == enCalcProjectionMatrixFunc_Ortho) {
		//平行投影行列。
		//プロジェクション行列を計算。
		m_projMatrix.MakeOrthoProjectionMatrix(
			m_viewVolumeWidth,		//ビューボリュームの幅。
			m_viewVolumeHeight,		//ビューボリュームの高さ
			m_near,
			m_far
		);
	}
}