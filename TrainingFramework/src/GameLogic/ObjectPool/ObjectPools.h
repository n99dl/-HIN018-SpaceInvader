#pragma once

#include "../GameManager/Singleton.h"
#include <list>
#include <GameLogic\Bullet.h>
#include <GameLogic\GameLogicConfig.h>
#include <GameObject\AnimationSprite.h>

class ObjectPools : public CSingleton<ObjectPools>
{
private:
	std::list<std::shared_ptr<Bullet>> m_listPlayerBullets;
	std::list<std::shared_ptr<Bullet>> m_listEnemyBullets;
	std::list<std::shared_ptr<Bullet>> m_listHomingBullets;
	std::list<std::shared_ptr<AnimationSprite>> m_listImpact;
	std::list<std::shared_ptr<AnimationSprite>> m_listExplosion;
	int totalBullet = 0;
	int totalAnimation = 0;
public:
	int GetTotalBullet();
	void BulletCreateCount();
	void AnimationCreateCount();
	void InitBulletPool();
	std::shared_ptr<Bullet> getPlayerBullet();
	std::shared_ptr<Bullet> getEnemyBullet();
	std::shared_ptr<AnimationSprite> getImpactAnimation();
	std::shared_ptr<AnimationSprite> getExplosionAnimation();
};

