#pragma once
#include <iostream>
#include "Player.h"
#include <GameLogic\Enemy.h>
#include <GameLogic\Bullet.h>
#include <GameLogic\Item.h>

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
	void HandleTouchEvents(int x, int y, int isPressed);
	std::shared_ptr<Player> GetPlayer();
	void AddBullet(std::shared_ptr<Bullet> NewBullet);
	void AddItem(std::shared_ptr<Item> NewItem);
	void AddScore(int amount);
	int GetScore();
private:
	std::shared_ptr<Player> m_Player;
	std::list<std::shared_ptr<Enemy>> m_listEnemy;
	std::list<std::shared_ptr<Bullet>> m_listBullet;
	std::list<std::shared_ptr<Item>> m_listItem;
	int KeyPressed = 0;
	int m_Score = 0;
	float m_GameTime = 0;
	float m_EnemySpamTime = 2.0f;
};

