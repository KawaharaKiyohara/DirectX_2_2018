#pragma once
//�e�ۃ}�l�[�W���[
class Bullet;
class BulletManager
{
public:
	BulletManager();
	~BulletManager();
	Bullet* NewBullet();
	void Update();
	void Draw();
private:
	std::vector<Bullet*> m_bullets;	//�e�ۂ̉ϒ��z��B
};

