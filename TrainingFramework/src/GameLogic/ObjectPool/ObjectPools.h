#pragma once

#include "../GameManager/Singleton.h"
#include <list>
#include <GameLogic\Bullet.h>
#include <GameLogic\GameLogicConfig.h>

class ObjectPools : public CSingleton<ObjectPools>
{
private:
	std::list<std::shared_ptr<Bullet>> m_listBullets;
public:
	void InitBulletPool();
	std::shared_ptr<Bullet> getBullet();
};

