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
	CreateEnemies();
}

void GameController::CreateEnemies()
{
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<DarkPlane> newEnemy = std::make_shared<DarkPlane>(rand() % screenWidth);
		m_listEnemy.push_back(newEnemy);
	}
}

void GameController::Draw()
{
	m_Player->Draw();
	for (auto it : m_listEnemy)
	{
		it->Draw();
	}
}

void GameController::Update(float dt)
{
	m_Player->Move(KeyPressed, dt);
	m_Player->Update(KeyPressed);
	for (auto it : m_listEnemy)
	{
		it->Update(dt);
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
		default:
			break;
		}
	}
}

void GameController::HandleTouchEvents(int x, int y, bool isPressed)
{
	m_Player->MoveByMouse(x, y);
}

std::shared_ptr<Player> GameController::GetPlayer()
{
	return std::shared_ptr<Player>();
}
