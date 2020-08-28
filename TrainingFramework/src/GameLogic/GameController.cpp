#include "GameController.h"
#include "../ControlConfig.h"

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
}

void GameController::Draw()
{
	m_Player->Draw();
}

void GameController::Update(float dt)
{
	m_Player->Move(KeyPressed, dt);
	m_Player->Update(KeyPressed);
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
