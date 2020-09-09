#pragma once
#include <iostream>
#include "Player.h"
#include <GameLogic\Enemy.h>
#include <GameLogic\Bullet.h>
#include <GameLogic\Item.h>
#include <AnimationSprite.h>
#include <ParalelBackground.h>

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
	void AddPlayerBullet(std::shared_ptr<Bullet> NewBullet);
	void AddEnemyBullet(std::shared_ptr<Bullet> NewBullet);
	void AddItem(std::shared_ptr<Item> NewItem);
	void AddScore(int amount);
	void AddAnimation(std::shared_ptr<AnimationSprite> NewAnimation);
	void SpamMinion();
	void CreateBoss();
	int GetPlayerHp();
	Vector2 GetPlayerPosition();
	int GetScore();
	void AlertMotorDestroyed();
private:
	void AddDarkPlane(Vector2 Position);
	void AddRandomSideCirclePlane(float vPos);
	void AddCirclePlane(float vPos, int type);
	void AddRandomMotor();
	std::shared_ptr<Player> m_Player;
	std::list<std::shared_ptr<Enemy>> m_listEnemy;
	std::list<std::shared_ptr<Bullet>> m_listPlayerBullet;
	std::list<std::shared_ptr<Bullet>> m_listEnemyBullet;
	std::list<std::shared_ptr<Item>> m_listItem;
	std::list<std::shared_ptr<AnimationSprite>> m_listAnimation;
	std::shared_ptr<ParalelBackground> m_background;
	int m_wave;
	int KeyPressed = 0;
	int m_Score = 0;
	float m_GameTime = 0;
	float m_EnemySpamTime = 2.0f;
	float m_SpecialEnemySpamTime = 0.0f;
	int m_totalMotor;
	int m_motorCreated;
};

