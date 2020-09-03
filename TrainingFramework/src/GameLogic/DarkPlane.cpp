#include "DarkPlane.h"
#include "GameLogicConfig.h"
#include "ResourceManagers.h"
#include <iostream>
#include <GameLogic\HitBox.h>
#include <GameLogic\GameController.h>


void DarkPlane::Die()
{
	std::cout << "Dark Plane die\n";
	GameController::GetInstance()->AddScore(E1_SCORE);
	Enemy::Die();
}

DarkPlane::DarkPlane()
{
	SetPosition(E1_START_POSITION);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("dark_plane");
	m_Sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_Sprite->SetSize(E1_SIZE_X, E1_SIZE_Y);
	m_HitBox = std::make_shared<HitBox>(m_Position, Vector2(E1_SIZE_X / 2.0 + E1_SIZE_X_OFFSET,
															E1_SIZE_Y / 2.0 + E1_SIZE_Y_OFFSET));
	m_Sprite->Set2DPosition(m_Position);
	m_Speed = E1_BASE_SPEED;
	m_Hp = E1_BASE_HP;
	m_As = E1_BASE_AS;
	//E1 move pattern
	m_MovePatern = Vector2(0, 1);
	//E1 bullet pattern
	m_BulletPatern = Vector2(0, 1);
}

DarkPlane::DarkPlane(float hPosition) : DarkPlane()
{
	m_Position.x = hPosition;
}

DarkPlane::~DarkPlane()
{
}

void DarkPlane::Update(float dt)
{
	Enemy::Update(dt);
	CheckActive();
}

void DarkPlane::Shoot()
{
	std::shared_ptr<Bullet> NewBullet = std::make_shared<Bullet>(m_Position, E1_BULLET);
	NewBullet->SetBulletPatern(m_BulletPatern);
	NewBullet->SetBulletSpeed(E1_BULLET_SPEED);
	GameController::GetInstance()->AddEnemyBullet(NewBullet);
}
