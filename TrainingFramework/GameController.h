#pragma once
#include <iostream>
#include "Player.h"

class GameController
{
public:
	GameController();
	~GameController();
	void Draw();
private:
	std::shared_ptr<Player> m_Player;
};

