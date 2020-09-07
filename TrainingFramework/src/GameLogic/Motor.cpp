#include "Motor.h"
#include "GameLogicConfig.h"
#include "ResourceManagers.h"
#include "GL_Utility.h"
#include <iostream>
#include <GameLogic\HitBox.h>
#include <GameLogic\GameController.h>
#include <time.h>


void Motor::Die()
{
	std::cout << "Motor die\n";
	GameController::GetInstance()->AddScore(E3_SCORE);
	Enemy::Die();
}

void Motor::GenerateDestination()
{
	srand(time(NULL));
	Vector2 space = E3_MOVE_SPACE;
	int xLim = space.x - E3_SIZE_X;
	int yLim = space.y - E3_SIZE_Y;
	float nx = rand() % xLim + E3_SIZE_X;
	float ny = rand() % yLim + E3_SIZE_Y;
	m_Destination = Vector2(nx, ny);
}

Motor::Motor()
{
	SetPosition(E3_START_POSITION);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("motor");
	m_Sprite = std::make_shared<Sprite2D>(model, shader, texture);	
	m_Sprite->SetSize(E3_SIZE_X, E3_SIZE_Y);
	m_HitBox = std::make_shared<HitBox>(m_Position, Vector2(E3_SIZE_X / 2.0 + E1_SIZE_X_OFFSET,
		E3_SIZE_Y / 2.0 + E1_SIZE_Y_OFFSET));
	m_Sprite->Set2DPosition(m_Position);
	m_Speed = E1_BASE_SPEED;
	m_Hp = E3_HP;
	m_As = E3_BASE_AS;
	int duration_in_int = E3_BASE_AS * 10;
	m_currentTime = (rand() % duration_in_int) * 0.1;
	//E1 move pattern
	m_MovePatern = Vector2(0, 1);
	//E1 bullet pattern
	m_BulletPatern = Vector2(0, 1);
	m_idleTime = 0.0f;
	m_IsIdling = false;
	GenerateDestination();
	m_MovePatern = GL_Utility::GetMoveVector(m_Position, m_Destination);
}

Motor::Motor(Vector2 Position) : Motor()
{
	m_Destination = Position;
	m_MovePatern = GL_Utility::GetMoveVector(m_Position, m_Destination);
}

Motor::~Motor()
{
}

void Motor::Update(float dt)
{
	Enemy::Update(dt);
	//std::cout << "Idle Time: " << m_idleTime << "\n";
	//std::cout << "Destination " << m_Destination.x << " " << m_Destination.y << "\n";
	if (!m_IsIdling)
	{
		if (abs(m_Position.x - m_Destination.x) <= 1.0f && abs(m_Position.y - m_Destination.y) <= 1.0f)
		{
			m_idleTime = E3_IDLE_TIME;
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

void Motor::Shoot()
{
	std::shared_ptr<Bullet> NewBullet = std::make_shared<Bullet>(m_Position, E3_BULLET);
	NewBullet->SetBulletSpeed(E3_BULLET_SPEED);
	GameController::GetInstance()->AddEnemyBullet(NewBullet);
}
