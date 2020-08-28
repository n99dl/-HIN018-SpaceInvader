#pragma once
#include <iostream>
#include "Player.h"

class GameController: public CSingleton<GameController>
{
public:
	GameController();
	~GameController();
	void CreatePlayer();
	void CreateLevel();
	void Draw();
	void Update(float dt);
	void HandleKeyEvents(int key, bool isPressed);
	void HandleTouchEvents(int x, int y, bool isPressed);
	std::shared_ptr<Player> GetPlayer();
private:
	std::shared_ptr<Player> m_Player;
	int KeyPressed = 0;
};

