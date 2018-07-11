#include "stdafx.h"
#include "BulletManager.h"
#include "Bullet.h"

BulletManager::BulletManager()
{
}


BulletManager::~BulletManager()
{
}
Bullet* BulletManager::NewBullet()
{
	Bullet* newBullet = new Bullet;
	m_bullets.push_back(newBullet);
	return newBullet;
}
void BulletManager::Update()
{
	for (auto& bullet : m_bullets) {
		bullet->Update();
	}
}
void BulletManager::Draw()
{
	for (auto& bullet : m_bullets) {
		bullet->Draw();
	}
}