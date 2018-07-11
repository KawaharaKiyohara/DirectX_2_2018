#pragma once
class Bullet
{
public:
	Bullet();
	~Bullet();
	void Update();
	void Draw();
	void SetPosition(CVector3 pos)
	{
		m_pos = pos;
	}
	void SetMoveSpeed(CVector3 speed)
	{
		m_moveSpeed += speed;
	}
private:
	SkinModel m_model;							//モデル。
	CVector3 m_pos = CVector3::Zero();			//座標。
	CVector3 m_moveSpeed = CVector3::Zero();	//移動速度。
};

