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
}

void GameController::Update(float dt)
{
	m_GameTime += dt;
	m_EnemySpamTime += dt;
	if (m_EnemySpamTime > 2.0f) //Let set this fix for now
	{
		CreateEnemies();
		m_EnemySpamTime -= 2.0f;
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
