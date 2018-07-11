#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "Path.h"

using namespace std;
Enemy::Enemy(CVector3 pos, CQuaternion rot, Player* player) :
	m_position(pos),
	m_rotation(rot),
	m_player(player)
{
	m_model.Init(L"Assets/modelData/enemy.cmo");
	//�p�X�ړ����ɑJ�ڂ���B
	m_currentPointNo = 0;
}
Enemy::~Enemy()
{
}
bool Enemy::IsFindPlayer()
{
	CVector3 enemyForward = CVector3::AxisZ();
	m_rotation.Multiply(enemyForward);
	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toPlayerDir = m_player->GetPosition() - m_position;
	//���K�����s���O�ɁA�v���C���[�܂ł̋��������߂Ă����B
	float toPlayerLen = toPlayerDir.Length();
	//���K���I
	toPlayerDir.Normalize();
	//enemyForward��toPlayerDir�Ƃ̓��ς��v�Z����B
	float d = enemyForward.Dot(toPlayerDir);
	//���ς̌��ʂ�acos�֐��ɓn���āAenemyForward��toPlayerDir�̂Ȃ��p�����߂�B
	float angle = acos(d);
	//����p����
	//fabsf�͐�Βl�����߂�֐��I
	//�p�x�̓}�C�i�X�����݂��邩��A��Βl�ɂ���B
	if (fabsf(angle) < CMath::DegToRad(45.0f)
		&& toPlayerLen < 300.0f
		) {
		//�������B
		return true;
	}
	//�����Ă��Ȃ��B
	return false;
}
//�p�X�ړ����̍X�V�����B
void Enemy::Update_StateMovePath()
{
	//�p�X���擾�B
	vector< PathPoint* >& pathArray = g_game->GetPath();
	//���̃|�C���g�ԍ������߂�B
	int nextPointNo = (m_currentPointNo + 1) % pathArray.size();
	//���̃|�C���g�Ɍ������x�N�g�������߂�B
	CVector3 vNextPointDir = pathArray[nextPointNo]->position 
						- pathArray[m_currentPointNo]->position;
	//���̃|�C���g�܂ł̋������v�Z����B
	float pathLen = vNextPointDir.Length();
	//���̃|�C���g�܂ł̃x�N�g���𐳋K�����đ傫��1�ɂ���B
	vNextPointDir.Normalize();
	//�G�l�~�[�̍��W�𓮂����B
	m_position += vNextPointDir * 2.0f;
	//�ړ���̍��W���p�X�̐�����Ɏˉe����B
	CVector3 posInPath = m_position - pathArray[m_currentPointNo]->position;
	//�p�X��ł̃v���C���[�̈ʒu���ˉe����B
	float t = posInPath.Dot(vNextPointDir);
	if (t > pathLen) {
		//�I�_�����Ă�ˁB
		m_position = pathArray[nextPointNo]->position;
		m_currentPointNo = nextPointNo;
	}
	//�������ς���B
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(vNextPointDir.x, vNextPointDir.z));

	//�v���C���̎���p����
	if (IsFindPlayer() == true) {
		//�v���C���[���������B
		//�v���C���[��ǐՏ�ԂɑJ�ڂ���B
		m_state = enState_FollowPlayer;
	}
}
//�v���C���[��ǐՒ��̍X�V�����B
void Enemy::Update_StateFollowPlayer()
{
	CVector3 toPlayer = m_player->GetPosition() - m_position;
	float len = toPlayer.Length();
	toPlayer.Normalize();
	m_position += toPlayer * 2.0f;

	if (len > 500.0f) {
		//������߂�p�X�ɋA��B
		ChangeStateReturnPath();
	}
	//�������ς���B
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(toPlayer.x, toPlayer.z));
}
//�p�X�ɋA�Ғ��̍X�V�����B
void Enemy::Update_ReturnPath()
{
	CVector3 toReturnPoint = m_returnPoint - m_startPosReturn;
	float len = toReturnPoint.Length();
	toReturnPoint.Normalize();
	m_position += toReturnPoint * 2.0f;
	CVector3 posInPath = m_position - m_startPosReturn;
	float t = posInPath.Dot(toReturnPoint);
	if (t > len) {
		//�Ƃ���������B
		m_position = m_returnPoint;
		m_state = enState_MovePath;
	}
	//�������ς���B
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(toReturnPoint.x, toReturnPoint.z));
}
void Enemy::ChangeStateReturnPath()
{
	//�A�ҊJ�n���W���L�����Ă����B
	
	m_startPosReturn = m_position;
	//���K�A�Ґ�ƂȂ�Am_returnPoint���v�Z����v���O�������L�q���܂��傤�B
	vector< PathPoint* >& pathArray = g_game->GetPath();
	//��ԋ߂��p�X�ɂ܂������A��B
	float fNearPathDist = FLT_MAX;
	for (int pointNo = 0; pointNo < pathArray.size(); pointNo++) {
		int nextPointNo = (pointNo + 1) % pathArray.size();
		//�n�_����v���C���[�ɐL�т�x�N�g�����v�Z����B
		CVector3 toPlayer = m_position - pathArray[pointNo]->position;
		CVector3 nextPointDir = pathArray[nextPointNo]->position
			- pathArray[pointNo]->position;
		float lenNextPoint = nextPointDir.Length();
		nextPointDir.Normalize();
		float dist = 0;
		CVector3 returnPoint;
		//
		float t = nextPointDir.Dot(toPlayer);
		if (t < 0.0f) {
			//���������p�X��ɂ��Ȃ��B
			//���̏ꍇ�͎n�_�܂ł̋����ɂ��Ƃ����B
			dist = (m_position - pathArray[pointNo]->position).Length();
			returnPoint = pathArray[pointNo]->position;
		}
		else if (t > lenNextPoint) {
			//�I�_�𒴂��Ă�B
			dist = (m_position - pathArray[nextPointNo]->position).Length();
			returnPoint = pathArray[nextPointNo]->position;
		}
		else {
			//�I���U���C���B�����̌�_�����߂�B
			returnPoint = pathArray[pointNo]->position + (nextPointDir * t);
			dist = (m_position - returnPoint).Length();
		}
		if (fNearPathDist > dist) {
			//�X�V�B
			fNearPathDist = dist;
			m_returnPoint = returnPoint;
			m_currentPointNo = pointNo;
		}
	}
	m_state = enState_ReturnPath;
}
void Enemy::Update()
{
	switch (m_state) {
	case enState_MovePath:
		Update_StateMovePath();
		break;
	case enState_FollowPlayer:
		Update_StateFollowPlayer();
		break;
	case enState_ReturnPath:
		Update_ReturnPath();
		break;
	}
	//���[���h�s������߂�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 3.0f, 3.0f, 3.0f });
}
void Enemy::Draw()
{
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
}
