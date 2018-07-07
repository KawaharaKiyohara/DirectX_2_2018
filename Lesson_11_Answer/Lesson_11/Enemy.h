#pragma once

#include "character/CharacterController.h"
class Player;

class Enemy
{
public:
	Enemy( CVector3 pos, CQuaternion rot, Player* player);
	~Enemy();
	void Update();
	void Draw();
private:
	enum State {
		State_Search,
		State_Tracking,
	};
	CVector3 m_position = CVector3::Zero();				//座標。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	SkinModel m_model;									//モデル。
	CVector3 m_moveSpeed = CVector3::Zero();
	Player* m_player = nullptr;
	State m_state = State_Search;
	CharacterController m_charaCon;
};

