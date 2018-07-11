#pragma once
//弾丸マネージャー
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
	std::vector<Bullet*> m_bullets;	//弾丸の可変長配列。
};

