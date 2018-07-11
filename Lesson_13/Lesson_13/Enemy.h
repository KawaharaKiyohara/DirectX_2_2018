#pragma once

class Player;
struct PathPoint;

class Enemy
{
public:
	Enemy( CVector3 pos, CQuaternion rot, Player* player);
	~Enemy();
	void Update();
	void Draw();
private:
	//�p�X�ړ����̍X�V�����B
	void Update_StateMovePath();
	//�v���C���[��ǐՒ��̍X�V�����B
	void Update_StateFollowPlayer();
	//�p�X�ɋA�Ғ��̍X�V�����B
	void Update_ReturnPath();
	//�v���C���[�𔭌������H
	bool IsFindPlayer();
	//�A�ҏ�ԂɑJ�ځB
	void ChangeStateReturnPath();
private:
	//�X�e�[�g�B
	enum EnState {
		enState_MovePath,		//�p�X����ړ����B
		enState_FollowPlayer,	//�v���C���[��ǐՒ��B
		enState_ReturnPath,		//�p�X�ɋA�Ғ��B
	};
	CVector3 m_returnPoint = CVector3::Zero();			//�A�ҍ��W�B
	CVector3 m_startPosReturn = CVector3::Zero();		//�A�҂��J�n�����Ƃ��̊J�n���W�B
	CVector3 m_position = CVector3::Zero();				//���W�B
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�B
	SkinModel m_model;									//���f���B
	Player* m_player = nullptr;
	EnState m_state = enState_MovePath;					//�p�X�ړ����B
	int m_currentPointNo = 0;	
};

