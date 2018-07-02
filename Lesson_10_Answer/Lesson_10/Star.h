#pragma once
class Player;
class Star
{
private:
	Player& m_player;		//プレイヤーの参照。
	SkinModel m_model;		//モデル。
	CVector3 m_position;	//座標。
	bool m_isDead = false;	//死亡フラグ。
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

