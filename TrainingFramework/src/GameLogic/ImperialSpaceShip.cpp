#include "ImperialSpaceShip.h"
#include "GameLogicConfig.h"
#include "ResourceManagers.h"
#include "GL_Utility.h"
#include <iostream>
#include <GameLogic\HitBox.h>
#include <GameLogic\GameController.h>
#include <time.h>


void ImperialSpaceShip::Die()
{
	if (m_Phase == E4_LAST_PHASE)
	{
		std::cout << "BOSS die \n";
		Enemy::Die(); 
		GameController::GetInstance()->AddScore(E4_SCORE);
		GameController::GetInstance()->Victory();
	}
	else
	{
		switch (m_Phase)
		{
		case 0:
			m_Phase++;
			m_Hp = E4_HP_2;
			m_maxHp = E4_HP_2;
			m_As -= 0.1;
			m_circleGunCooldown -= 1.0;
			m_circleGunTiming = m_circleGunCooldown;
			DropItem();
			DropItem();
			break;
		case 1:
			m_Phase++;
			m_As -= 0.15;
			m_circleGunCooldown -= 1.5;
			m_circleGunTiming = m_circleGunCooldown;
			m_Hp = E4_HP_3;
			m_maxHp = E4_HP_3;
			DropItem();
			DropItem();
			DropItem();
			break;
		}
	}
}

void ImperialSpaceShip::GenerateDestination()
{
	Vector2 space = E3_MOVE_SPACE;
	int xLim = space.x - E4_SIZE_X;
	int yLim = space.y - E4_SIZE_Y;
	float nx = rand() % xLim + E4_SIZE_X / 2;
	float ny = rand() % yLim + E4_SIZE_Y / 2;
	m_Destination = Vector2(nx, ny);
}

void ImperialSpaceShip::CreateE1BulletWithPattern(Vector2 Pattern)
{
	//std::shared_ptr<Bullet> NewBullet = std::make_shared<Bullet>(m_Position, E1_BULLET);
	std::shared_ptr<Bullet> NewBullet = ObjectPools::GetInstance()->getEnemyBullet();
	NewBullet->InitBulletWithTypeAndPosition(m_Position, E1_BULLET);

	NewBullet->SetBulletPatern(Pattern);
	NewBullet->SetBulletSpeed(E1_BULLET_SPEED);
	GameController::GetInstance()->AddEnemyBullet(NewBullet);
}

ImperialSpaceShip::ImperialSpaceShip()
{
	SetPosition(E3_START_POSITION);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("imperial_space_ship");
	m_Sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_Sprite->SetSize(E4_SIZE_X, E4_SIZE_Y);
	m_HitBox = std::make_shared<HitBox>(m_Position, Vector2(E4_SIZE_X / 2.0 - E4_OFFSET_X,
		E4_SIZE_Y / 2.0 - E4_OFFSET_Y));
	m_Sprite->Set2DPosition(m_Position);
	m_Speed = E4_BASE_SPEED;
	m_Hp = E4_HP_1;
	m_As = E4_SUB_GUN_CD;
	int duration_in_int = E4_SUB_GUN_CD * 10;
	m_currentTime = 0.0f;
	//E1 move pattern
	m_MovePatern = Vector2(0, 1);
	//E1 bullet pattern
	m_BulletPatern = Vector2(0, 1);
	m_idleTime = 0.0f;
	m_IsIdling = false;
	m_circleGunTiming = E4_CIRCLE_GUN_CD;
	m_circleGunCooldown = E4_CIRCLE_GUN_CD;
	GenerateDestination();
	m_MovePatern = GL_Utility::GetMoveVector(m_Position, m_Destination);
	m_itemOdd = E3_ITEM_ODD;
	m_Phase = 0;
	m_maxHp = E4_HP_1;
	m_IsBoss = true;
}

ImperialSpaceShip::ImperialSpaceShip(Vector2 Position) : ImperialSpaceShip()
{
	m_Destination = Position;
	m_MovePatern = GL_Utility::GetMoveVector(m_Position, m_Destination);
}

ImperialSpaceShip::~ImperialSpaceShip()
{
}

void ImperialSpaceShip::Update(float dt)
{
	//std::cout << "Boss test :" << m_Hp << "\n";
	Enemy::Update(dt);
	Enemy::Update(dt);
	//std::cout << "Idle Time: " << m_idleTime << "\n";
	//std::cout << "Destination " << m_Destination.x << " " << m_Destination.y << "\n";
	ShootCircle();
	m_circleGunTiming += dt;
	if (!m_IsIdling)
	{
		if (abs(m_Position.x - m_Destination.x) <= 10.0f && abs(m_Position.y - m_Destination.y) <= 10.0f)
		{
			m_idleTime = E4_IDLE_TIME;
			m_IsIdling = true;
			m_MovePatern = Vector2(0, 0);
		}
	}
	else
	{
		m_idleTime -= dt;
		if (m_idleTime <= 0.0f)
		{
			m_IsIdling = false;
			GenerateDestination();
			m_MovePatern = GL_Utility::GetMoveVector(m_Position, m_Destination);
		}
	}
	CheckActive();
}

//Sub Gun Shoot
void ImperialSpaceShip::Shoot()
{
	float thetaBase = M_PI / 24;
	for (int i = 0; i <= 4; i++)
	{
		float theta = thetaBase + (float)(i) * (M_PI / 12.0);
		Vector2 Patern = GL_Utility::GetMoveVector(theta);
		CreateE1BulletWithPattern(Patern);
		theta = -thetaBase - (float)(i) * (M_PI / 12.0);
		Patern = GL_Utility::GetMoveVector(theta);
		CreateE1BulletWithPattern(Patern);
	}
}

float ImperialSpaceShip::GetHpPercent()
{
	float hp = m_Hp;
	float maxHp = m_maxHp;
	return hp / maxHp;
}

void ImperialSpaceShip::ShootCircle()
{
	if (m_circleGunTiming >= m_circleGunCooldown)
	{
		Vector2 Position = m_Position;
		Vector2 BulletPosition;
		float theta = 2 * M_PI / 4;
		float radius = 20.0f;
		for (int i = 0; i < 4; i++)
		{
			BulletPosition.x = Position.x + radius * sinf(theta * i);
			BulletPosition.y = Position.y + radius * cosf(theta * i);
			CreateBulletAt(BulletPosition);
		}
		m_circleGunTiming -= m_circleGunCooldown;
	}
}

void ImperialSpaceShip::CreateBulletAt(Vector2 Position)
{
	std::shared_ptr<Bullet> NewBullet = std::make_shared<Bullet>(Position, E1_BULLET);
	Vector2 p_Position = GameController::GetInstance()->GetPlayerPosition();
	//float dot = (p_Position.y - m_Position.y);
	//float det = (p_Position.x - m_Position.x);
	//float theta = atan2f(det, dot);
	//float theta = GL_Utility::GetAngle(m_Position, p_Position);
	//Vector2 p_BulletPatern = Vector2(sinf(theta), cosf(theta)) * 1.0;
	Vector2 p_BulletPatern = GL_Utility::GetMoveVector(m_Position, p_Position);
	NewBullet->SetBulletPatern(p_BulletPatern);
	NewBullet->SetBulletSpeed(E4_CIRCLE_SPEED);
	GameController::GetInstance()->AddEnemyBullet(NewBullet);
}

int ImperialSpaceShip::GetPhase()
{
	return m_Phase + 1;
}
