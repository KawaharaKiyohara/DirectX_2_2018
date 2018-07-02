#pragma once
class Player;
class Star
{
private:
	Player& m_player;		//�v���C���[�̎Q�ƁB
	SkinModel m_model;		//���f���B
	CVector3 m_position;	//���W�B
	bool m_isDead = false;	//���S�t���O�B
public:
	Star( Player& player, CVector3 pos );
	~Star();
	void Update();
	void Draw();
	bool IsDead()
	{
		return m_isDead;
	}
};

