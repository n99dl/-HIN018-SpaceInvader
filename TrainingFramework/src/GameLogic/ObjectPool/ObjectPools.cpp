#include "ObjectPools.h"

void ObjectPools::InitBulletPool()
{
	for (int i = 1; i <= 10; i++)
	{
		auto newBullet = std::make_shared<Bullet>(PLAYER_BULLET);
		m_listBullets.push_back(newBullet);
	}
}

std::shared_ptr<Bullet> ObjectPools::getBullet()
{
	for (auto bullet : m_listBullets)
	{
		if (!bullet->isActive())
			return bullet;
	}
	auto newBullet = std::make_shared<Bullet>(PLAYER_BULLET);
	m_listBullets.push_back(newBullet);
	return newBullet;
}
