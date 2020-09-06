#include "CirclePlane.h"
#include "GameLogicConfig.h"
#include "ResourceManagers.h"
#include <iostream>
#include <GameLogic\HitBox.h>
#include <GameLogic\GameController.h>


void CirclePlane::Die()
{
	std::cout << "Dark Plane die\n";
	GameController::GetInstance()->AddScore(E1_SCORE);
	Enemy::Die();
}

CirclePlane::CirclePlane()
{
	SetPosition(E1_START_POSITION);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("CirclePlane");
	m_Sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_Sprite->SetSize(E1_SIZE_X, E1_SIZE_Y);
	m_HitBox = std::make_shared<HitBox>(m_Position, Vector2(E1_SIZE_X / 2.0 + E1_SIZE_X_OFFSET,
		E1_SIZE_Y / 2.0 + E1_SIZE_Y_OFFSET));
	m_Sprite->Set2DPosition(m_Position);
	m_Speed = E1_BASE_SPEED;
	m_Hp = E1_BASE_HP;
	m_As = E2_BASE_AS;
	//E1 move pattern
	m_MovePatern = Vector2(0, 1);
	//E1 bullet pattern
	m_BulletPatern = Vector2(0, 1);
}

CirclePlane::CirclePlane(float hPosition) : CirclePlane()
{
	m_Position.x = hPosition;
}

CirclePlane::~CirclePlane()
{
}

void CirclePlane::Update(float dt)
{
	Enemy::Update(dt);
	CheckActive();
}

void CirclePlane::Shoot()
{
	Vector2 Position = m_Position;
	Vector2 BulletPosition;
	float theta = 2 * M_PI / 6;
	float radius = 30.0f;
	for (int i = 0; i < 6; i++)
	{
		BulletPosition.x = Position.x + radius * sinf(theta * i);
		BulletPosition.y = Position.y + radius * cosf(theta * i);
		CreateBulletAt(BulletPosition);
	}

}

void CirclePlane::CreateBulletAt(Vector2 Position)
{
	std::shared_ptr<Bullet> NewBullet = std::make_shared<Bullet>(Position, E1_BULLET);
	Vector2 p_Position = GameController::GetInstance()->GetPlayerPosition();
	float dot = (p_Position.y - m_Position.y);
	float det = (p_Position.x - m_Position.x);
	float theta = atan2f(det, dot);
	Vector2 p_BulletPatern = Vector2(sinf(theta), cosf(theta)) * 1.0;
	NewBullet->SetBulletPatern(p_BulletPatern);
	NewBullet->SetBulletSpeed(E2_BULLET_SPEED);
	GameController::GetInstance()->AddEnemyBullet(NewBullet);
}
