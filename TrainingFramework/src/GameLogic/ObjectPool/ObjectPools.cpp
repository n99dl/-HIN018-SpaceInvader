#include "ObjectPools.h"
#include "../GameManager/ResourceManagers.h"

int ObjectPools::GetTotalBullet()
{
	return totalBullet;
}

void ObjectPools::BulletCreateCount()
{
	totalBullet++;
}

void ObjectPools::AnimationCreateCount()
{
	totalAnimation++;
}

void ObjectPools::InitBulletPool()
{
	if (m_listPlayerBullets.empty())
	{
		for (int i = 1; i <= 10; i++)
		{
			auto newBullet = std::make_shared<Bullet>(PLAYER_BULLET);
			m_listPlayerBullets.push_back(newBullet);
			newBullet = std::make_shared<Bullet>(E1_BULLET);
			m_listEnemyBullets.push_back(newBullet);
		}
	}
	if (m_listImpact.empty())
	{
		for (int i = 1; i <= 10; i++)
		{
			auto texture = ResourceManagers::GetInstance()->GetTexture("impact");
			auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
			std::shared_ptr<AnimationSprite> impactAnimation = std::make_shared<AnimationSprite>(model, shader, texture, I_NUM_FRAME, I_FRAME_TIME, false);
			impactAnimation->Set2DPosition(-100, -100);
			m_listImpact.push_back(impactAnimation);
		}
	}
	if (m_listExplosion.empty())
	{
		for (int i = 1; i <= 10; i++)
		{
			auto texture = ResourceManagers::GetInstance()->GetTexture("red_explosion");
			auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
			std::shared_ptr<AnimationSprite> Explosion = std::make_shared<AnimationSprite>(model, shader, texture, RE_NUM_FRAME, RE_FRAME_TIME, false);
			Explosion->Set2DPosition(-100, -100);
			m_listExplosion.push_back(Explosion);
		}
	}
}

std::shared_ptr<Bullet> ObjectPools::getPlayerBullet()
{
	for (auto bullet : m_listPlayerBullets)
	{
		if (!bullet->isActive())
		{
			//std::cout << "Get player bullet from pool\n";
			return bullet;
		}
	}
	//std::cout << "New player bullet\n";
	auto newBullet = std::make_shared<Bullet>(PLAYER_BULLET);
	m_listPlayerBullets.push_back(newBullet);
	return newBullet;
}

std::shared_ptr<Bullet> ObjectPools::getEnemyBullet()
{
	for (auto bullet : m_listEnemyBullets)
	{
		if (!bullet->isActive())
		{
			//std::cout << "Get enemy bullet from pool\n";
			return bullet;
		}
	}
	//std::cout << "New enemy bullet " + m_listEnemyBullets.size() << "\n";
	auto newBullet = std::make_shared<Bullet>(E1_BULLET);
	m_listEnemyBullets.push_back(newBullet);
	return newBullet;
}

std::shared_ptr<AnimationSprite> ObjectPools::getImpactAnimation()
{
	for (auto impact : m_listImpact)
	{
		if (!impact->IsActive())
		{
			//std::cout << "Get impact Animation from pool\n";
			return impact;
		}
	}
	//std::cout << "New impact Animation " + m_listImpact.size() << "\n";
	auto texture = ResourceManagers::GetInstance()->GetTexture("impact");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	std::shared_ptr<AnimationSprite> animation = std::make_shared<AnimationSprite>(model, shader, texture, I_NUM_FRAME, I_FRAME_TIME, false);
	animation->Set2DPosition(-100, -100);
	m_listImpact.push_back(animation);
	return animation;
}

std::shared_ptr<AnimationSprite> ObjectPools::getExplosionAnimation()
{
	for (auto explosion : m_listExplosion)
	{
		if (!explosion->IsActive())
		{
			//std::cout << "Get explosion Animation from pool\n";
			return explosion;
		}
	}
	//std::cout << "New explosion Animation " + m_listExplosion.size() << "\n";
	auto texture = ResourceManagers::GetInstance()->GetTexture("red_explosion");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	std::shared_ptr<AnimationSprite> animation = std::make_shared<AnimationSprite>(model, shader, texture, RE_NUM_FRAME, RE_FRAME_TIME, false);
	animation->Set2DPosition(-100, -100);
	m_listExplosion.push_back(animation);
	return animation;
}
