#include "GameController.h"
#include "../ControlConfig.h"
#include <GameLogic\DarkPlane.h>

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GameController::GameController()
{
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
}

void GameController::CreateEnemies()
{
	std::shared_ptr<DarkPlane> newEnemy = std::make_shared<DarkPlane>(rand() % screenWidth);
	m_listEnemy.push_back(newEnemy);
}

void GameController::Draw()
{
	m_Player->Draw();
	for (auto it : m_listEnemy)
	{
		it->Draw();
	}
	for (auto it : m_listBullet)
	{
		it->Draw();
	}
	for (auto it : m_listItem)
	{
		it->Draw();
	}
}

void GameController::Update(float dt)
{
	m_GameTime += dt;
	m_EnemySpamTime += dt;
	//Spam enemies
	//Temporary difficulty system (need improvement)
	float BaseSpamTime = 2.0f;
	if (m_Score > 100)
		BaseSpamTime = 1.5f;
	if (m_Score > 200)
		BaseSpamTime = 1.0f;
	if (m_Score > 300)
		BaseSpamTime = 0.5f;
	if (m_EnemySpamTime > BaseSpamTime)
	{
		CreateEnemies();
		m_EnemySpamTime -= BaseSpamTime;
	}
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
	//Update Bullet
	{
		std::list<std::shared_ptr<Bullet>>::iterator i = m_listBullet.begin();
		while (i != m_listBullet.end())
		{
			(*i)->Update(dt);
			bool isActive = (*i)->isActive();
			if (!isActive)
			{
				m_listBullet.erase(i++);  // alternatively, i = items.erase(i);
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
	//Collision Check
	for (auto enemy : m_listEnemy)
	{
		for (auto bullet : m_listBullet)
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

void GameController::AddBullet(std::shared_ptr<Bullet> NewBullet)
{
	m_listBullet.push_back(NewBullet);
}

void GameController::AddItem(std::shared_ptr<Item> NewItem)
{
	m_listItem.push_back(NewItem);
}

void GameController::AddScore(int amount)
{
	m_Score += amount;
}

int GameController::GetScore()
{
	return m_Score;
}
