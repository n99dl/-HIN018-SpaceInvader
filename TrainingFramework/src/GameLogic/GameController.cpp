#include "GameController.h"
#include "../ControlConfig.h"
#include <GameLogic\DarkPlane.h>
#include <GameLogic\CirclePlane.h>
#include <time.h>
#include <GameLogic\Motor.h>

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GameController::GameController()
{
	m_background = std::make_shared<ParalelBackground>();
}

GameController::~GameController()
{
}

void GameController::CreatePlayer()
{
	std::cout << "Player created\n";
	m_Player = std::make_shared<Player>();
}

void GameController::CreateLevel()
{
	CreatePlayer();

	std::shared_ptr<Motor> newEnemy;
	newEnemy = std::make_shared<Motor>(Vector2(200, 200));
	m_listEnemy.push_back(newEnemy);
}

void GameController::CreateEnemies()
{
	float odd = ((float)(rand() % 1000)) / 1000.0;
	//Dark Plane Spam
	if (odd >= 1.0 - E1_ODD)
	{
		std::shared_ptr<DarkPlane> newEnemy;
		newEnemy = std::make_shared<DarkPlane>( 30 + rand() % (screenWidth - 30));
		m_listEnemy.push_back(newEnemy);
	}

	//Circle Plane Spam
	odd = ((float)(rand() % 1000)) / 1000.0;
	if (m_Score >= 500)
	{
		if (odd >= 1.0 - E2_ODD)
		{
			std::shared_ptr<CirclePlane> newEnemy;
			newEnemy = std::make_shared<CirclePlane>(rand() % 270 + 30);
			m_listEnemy.push_back(newEnemy);
		}
	}
	//Motor Spam
	odd = ((float)(rand() % 1000)) / 1000.0;
	if (m_Score >= 10)
	{
		if (odd >= 1.0 - E3_ODD)
		{
			std::shared_ptr<Motor> newEnemy;
			newEnemy = std::make_shared<Motor>();
			m_listEnemy.push_back(newEnemy);
		}
	}
}

void GameController::Draw()
{
	m_background->Draw();
	m_Player->Draw();
	for (auto it : m_listEnemy)
	{
		it->Draw();
	}
	for (auto it : m_listPlayerBullet)
	{
		it->Draw();
	}
	for (auto it : m_listItem)
	{
		it->Draw();
	}
	for (auto it : m_listAnimation)
	{
		it->Draw();
	}
	for (auto it : m_listEnemyBullet)
	{
		it->Draw();
	}
}

void GameController::Update(float dt)
{
	m_GameTime += dt;
	m_EnemySpamTime += dt;
	m_background->Update(dt);
	//Spam enemies
	//Temporary difficulty system (need improvement)
	//SpamMinion();
	//Update Player
	m_Player->Move(KeyPressed, dt);
	/*if (KeyPressed & SHOOT)
		m_Player->SetIsShooting(true);
	else
		m_Player->SetIsShooting(false);*/
	m_Player->Update(dt);
	//Update Enemy
	{
		std::list<std::shared_ptr<Enemy>>::iterator i = m_listEnemy.begin();
		while (i != m_listEnemy.end())
		{
			(*i)->Update(dt);
			bool isActive = (*i)->isActive();
			if (!isActive)
			{
				m_listEnemy.erase(i++);  // alternatively, i = items.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
	//Update PBullet
	{
		std::list<std::shared_ptr<Bullet>>::iterator i = m_listPlayerBullet.begin();
		while (i != m_listPlayerBullet.end())
		{
			(*i)->Update(dt);
			bool isActive = (*i)->isActive();
			if (!isActive)
			{
				m_listPlayerBullet.erase(i++);  // alternatively, i = items.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
	//Update EBullet
	{
		std::list<std::shared_ptr<Bullet>>::iterator i = m_listEnemyBullet.begin();
		while (i != m_listEnemyBullet.end())
		{
			(*i)->Update(dt);
			bool isActive = (*i)->isActive();
			if (!isActive)
			{
				m_listEnemyBullet.erase(i++);  // alternatively, i = items.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
	//Update Item
	{
		std::list<std::shared_ptr<Item>>::iterator i = m_listItem.begin();
		while (i != m_listItem.end())
		{
			(*i)->Update(dt);
			bool isActive = (*i)->isActive();
			if (!isActive)
			{
				m_listItem.erase(i++);  // alternatively, i = items.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
	//Update Animation
	{
		std::list<std::shared_ptr<AnimationSprite>>::iterator i = m_listAnimation.begin();
		while (i != m_listAnimation.end())
		{
			(*i)->Update(dt);
			bool isActive = (*i)->IsActive();
			if (!isActive)
			{
				m_listAnimation.erase(i++);  // alternatively, i = items.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
	//Collision Check
	for (auto enemy : m_listEnemy)
	{
		for (auto bullet : m_listPlayerBullet)
			if (bullet->IsCollide(enemy))
			{
				enemy->DamageBy(bullet);
				bullet->SelfDestruct();
			}
	}

	for (auto item : m_listItem)
	{
		if (item->IsCollide(m_Player))
		{
			m_Player->ConsumeItem(item);
			item->Destroy();
		}
	}

	for (auto bullet : m_listEnemyBullet)
	{
		if (bullet->IsCollide(m_Player))
		{
			m_Player->DamageBy(bullet);
			bullet->SelfDestruct();
		}
	}
}

void GameController::HandleKeyEvents(int key, bool isPressed)
{
	if (isPressed)
	{
		switch (key)
		{
		case 'W':
			KeyPressed |= MOVE_UP;
			break;
		case 'S':
			KeyPressed |= MOVE_DOWN;
			break;
		case 'A':
			KeyPressed |= MOVE_LEFT;
			break;
		case 'D':
			KeyPressed |= MOVE_RIGHT;
			break;
		case 32:
			KeyPressed |= SHOOT;
		defualt:
			break;
		}
	}
	else {
		switch (key)
		{
		case 'W':
			KeyPressed ^= MOVE_UP;
			break;
		case 'S':
			KeyPressed ^= MOVE_DOWN;
			break;
		case 'A':
			KeyPressed ^= MOVE_LEFT;
			break;
		case 'D':
			KeyPressed ^= MOVE_RIGHT;
			break;
		case 32:
			KeyPressed ^= SHOOT;
		default:
			break;
		}
	}
}

void GameController::HandleTouchEvents(int x, int y, int isPressed)
{
	m_Player->MoveByMouse(x, y);
	if (isPressed == 1)
	{
		m_Player->SetIsShooting(true);
	} else if (isPressed == 0)
		m_Player->SetIsShooting(false);
}

std::shared_ptr<Player> GameController::GetPlayer()
{
	return std::shared_ptr<Player>();
}

void GameController::AddPlayerBullet(std::shared_ptr<Bullet> NewBullet)
{
	m_listPlayerBullet.push_back(NewBullet);
}

void GameController::AddEnemyBullet(std::shared_ptr<Bullet> NewBullet)
{
	m_listEnemyBullet.push_back(NewBullet);
}

void GameController::AddItem(std::shared_ptr<Item> NewItem)
{
	m_listItem.push_back(NewItem);
}

void GameController::AddScore(int amount)
{
	m_Score += amount;
}

void GameController::AddAnimation(std::shared_ptr<AnimationSprite> NewAnimation)
{
	m_listAnimation.push_back(NewAnimation);
}

void GameController::SpamMinion()
{
	float BaseSpamTime = 2.0f;
	if (m_Score > 300)
		BaseSpamTime = 1.5f;
	if (m_Score > 1000)
		BaseSpamTime = 1.0f;
	if (m_Score > 2000)
		BaseSpamTime = 0.8f;
	if (m_EnemySpamTime > BaseSpamTime)
	{
		CreateEnemies();
		m_EnemySpamTime -= BaseSpamTime;
	}
}

int GameController::GetPlayerHp()
{
	return m_Player->GetHp();
}

Vector2 GameController::GetPlayerPosition()
{
	return m_Player->GetPosition();
}

int GameController::GetScore()
{
	return m_Score;
}
