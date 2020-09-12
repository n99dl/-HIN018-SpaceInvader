#include "GameController.h"
#include "../ControlConfig.h"
#include <GameLogic\DarkPlane.h>
#include <GameLogic\CirclePlane.h>
#include <time.h>
#include <GameLogic\Motor.h>
#include <GameLogic\ImperialSpaceShip.h>

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GameController::GameController()
{
	m_background = std::make_shared<ParalelBackground>();
}

GameController::~GameController()
{
}

void GameController::Init()
{
	m_listEnemy.clear();
	m_listPlayerBullet.clear();
	m_listEnemyBullet.clear();
	m_listEnemy.clear();
}

void GameController::CreatePlayer()
{
	std::cout << "Player created\n";
	m_Player = std::make_shared<Player>();
}

void GameController::CreateLevel()
{
	CreatePlayer();
	m_wave = 0;
	m_totalMotor = 0;
	m_motorCreated = 0;
	m_bossPhase = false;
	m_gameOverCountDown = 999999999.0f;
	//cheat , teehee
	m_Player->PowerUp();
	m_Player->PowerUp();
	m_Player->PowerUp();
	m_Player->PowerUp();
	m_Player->PowerUp();
	//m_Player->HackBulletPower();
	m_Player->PowerUp();
	m_Player->PowerUp();
	m_Player->PowerUp();
	//m_Player->PowerUp();
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
	m_SpecialEnemySpamTime += dt;
	m_background->Update(dt);
	m_gameOverCountDown -= dt;
	if (m_gameOverCountDown <= 0)
	{
		GameOver();
	}
	//Spam enemies
	//Temporary difficulty system (need improvement)
	if (m_totalMotor >= 0)
		SpamMinion();
	else
		CreateBoss();
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
		if (enemy->IsCollide(m_Player))
		{
			m_Player->DamageBy(enemy);
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
	return m_Player;
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
	float base_spam_time = 2.0;
	if (m_GameTime >= 3.0 && m_wave < 1)
	{
		m_wave = 1;
		std::cout << "set to 1\n";
		m_EnemySpamTime = 2.0f;
	}
	if (m_GameTime >= 15.0 && m_wave < 2)
	{
		m_wave = 2;
	}
	if (m_GameTime >= 40.0 && m_wave < 3)
	{
		m_wave = 3;
		m_SpecialEnemySpamTime = 0.0f;
		m_EnemySpamTime = 8.0f;
	}
	if (m_GameTime >= 10.0 && m_wave < 4)
	{
		m_wave = 4;
		m_SpecialEnemySpamTime = 0.0f;
		m_EnemySpamTime = 2.0f;
	}
	float base_special_cd = 3.0; //?? name pls
	//Wave 1
	switch (m_wave)
	{
	case 1:
		if (m_EnemySpamTime >= base_spam_time)
		{
			Vector2 Position = Vector2(rand() % (screenWidth - 30) + 30, -30);
			AddDarkPlane(Position);
			m_EnemySpamTime -= base_spam_time;
		}
		break;
	case 2:
		base_spam_time = 1.8f;
		if (m_EnemySpamTime >= base_spam_time)
		{
			Vector2 Position = Vector2(rand() % (screenWidth - 30) + 30, -30);
			AddDarkPlane(Position);
			m_EnemySpamTime -= base_spam_time;
			float vPos = rand() % 300;
			AddRandomSideCirclePlane(vPos);
		}
		break;
	case 3:
		base_spam_time = 6.0f;
		if (m_GameTime >= 60.0)
		{
			base_spam_time -= 1.0f;
			base_special_cd -= 1.0f;
		}
		if (m_EnemySpamTime >= base_spam_time)
		{
			float xPos = rand() % (screenWidth - 60 * 3) + 30 * 3;
			Vector2 InitPos = Vector2(xPos, -50);
			AddDarkPlane(InitPos);
			for (int i = 1; i < 3; i++)
			{
				Vector2 WingPos = InitPos + Vector2(-30, -30) * i;
				AddDarkPlane(WingPos);
				WingPos = InitPos + Vector2(30, -30) * i;
				AddDarkPlane(WingPos);
			}
			m_EnemySpamTime -= base_spam_time;
		}
		if (m_SpecialEnemySpamTime >= base_special_cd)
		{
			float vPos = rand() % 300;
			AddCirclePlane(vPos, 0);
			AddCirclePlane(vPos, 1);
			m_SpecialEnemySpamTime -= base_special_cd;
		}
		break;
	case 4:
		base_spam_time = 5.0f;
		if (m_EnemySpamTime >= base_spam_time)
		{
			AddRandomMotor();
			m_SpecialEnemySpamTime -= 5.0;
			m_EnemySpamTime -= base_spam_time;
		}
	}
}

void GameController::CreateBoss()
{
	if (m_EnemySpamTime > 0.0f)
	{
		m_Boss = std::make_shared<ImperialSpaceShip>(Vector2(200, 200));
		m_listEnemy.push_back(m_Boss);
		m_EnemySpamTime = -99999999.0f;
	}
	m_bossPhase = true;
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

int GameController::GetPlayerPower()
{
	return m_Player->GetPower();
}

void GameController::AddDarkPlane(Vector2 Position)
{
	std::shared_ptr<DarkPlane> newEnemy;
	newEnemy = std::make_shared<DarkPlane>(1);
	newEnemy->SetPosition(Position);
	m_listEnemy.push_back(newEnemy);
}

void GameController::AddRandomSideCirclePlane(float vPos)
{
	std::shared_ptr<CirclePlane> newEnemy;
	newEnemy = std::make_shared<CirclePlane>(vPos);
	m_listEnemy.push_back(newEnemy);
}

void GameController::AddCirclePlane(float vPos, int type)
{
	std::shared_ptr<CirclePlane> newEnemy;
	newEnemy = std::make_shared<CirclePlane>(vPos, type);
	m_listEnemy.push_back(newEnemy);
}

void GameController::AddRandomMotor()
{
	if (m_motorCreated <= 5)
	{
		std::shared_ptr<Motor> newEnemy;
		newEnemy = std::make_shared<Motor>();
		m_listEnemy.push_back(newEnemy);
		m_motorCreated++;
		m_totalMotor++;
	}
}

void GameController::AlertMotorDestroyed()
{
	//A lazy way to check if all motor destroyed
	m_totalMotor--;
	if (m_totalMotor == 0) m_totalMotor--;
}

bool GameController::IsFightingBoss()
{
	return m_bossPhase;
}

float GameController::GetBossHpPercent()
{
	if (!IsFightingBoss())
		return 0;
	else
		return m_Boss->GetHpPercent();
}

int GameController::GetBossPhase()
{
	return m_Boss->GetPhase();
}

int GameController::GetWave()
{
	return m_wave;
}

void GameController::GameOver()
{
	std::shared_ptr<GameStateBase> currentState  = GameStateMachine::GetInstance()->CurrentState();
	GameStateMachine::GetInstance()->PopState();
	GameStateMachine::GetInstance()->PushState(StateTypes::STATE_GameOver);
	MediaPlayer::GetInstance()->StopAllSound();
}

void GameController::Victory()
{
	m_wave++;
	StartGameOverCountDown();
}

void GameController::StartGameOverCountDown()
{
	m_gameOverCountDown = 5.0f;
}
