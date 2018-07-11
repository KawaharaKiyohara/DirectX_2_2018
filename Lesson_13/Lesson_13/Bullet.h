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
	SkinModel m_model;							//���f���B
	CVector3 m_pos = CVector3::Zero();			//���W�B
	CVector3 m_moveSpeed = CVector3::Zero();	//�ړ����x�B
};

