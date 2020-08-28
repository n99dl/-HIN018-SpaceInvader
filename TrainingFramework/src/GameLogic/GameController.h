#pragma once
#include <iostream>
#include "Player.h"
#include <GameLogic\Enemy.h>

class GameController: public CSingleton<GameController>
{
public:
	GameController();
	~GameController();
	void CreatePlayer();
	void CreateLevel();
	void CreateEnemies();
	void Draw();
	void Update(float dt);
	void HandleKeyEvents(int key, bool isPressed);
	void HandleTouchEvents(int x, int y, bool isPressed);
	std::shared_ptr<Player> GetPlayer();
private:
	std::shared_ptr<Player> m_Player;
	std::list<std::shared_ptr<Enemy>> m_listEnemy;
	int KeyPressed = 0;
};

