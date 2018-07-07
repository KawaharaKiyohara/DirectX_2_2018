#pragma once

class Player;

class Enemy
{
public:
	Enemy( CVector3 pos, CQuaternion rot, Player* player);
	~Enemy();
	void Update();
	void Draw();
private:
	CVector3 m_position = CVector3::Zero();				//座標。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	SkinModel m_model;									//モデル。
	Player* m_player = nullptr;
};

