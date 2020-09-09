#include "CirclePlane.h"
#include "GameLogicConfig.h"
#include "ResourceManagers.h"
#include "GL_Utility.h"
#include <iostream>
#include <GameLogic\HitBox.h>
#include <GameLogic\GameController.h>


void CirclePlane::Die()
{
	std::cout << "Dark Plane die\n";
	GameController::GetInstance()->AddScore(E2_SCORE);
	Enemy::Die();
}

CirclePlane::CirclePlane()
{
	SetPosition(E2_START_POSITION);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("CirclePlane");
	m_Sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_Sprite->SetSize(E1_SIZE_X, E1_SIZE_Y);
	m_HitBox = std::make_shared<HitBox>(m_Position, Vector2(E1_SIZE_X / 2.0 + E1_SIZE_X_OFFSET,
		E1_SIZE_Y / 2.0 + E1_SIZE_Y_OFFSET));
	m_Sprite->Set2DPosition(m_Position);
	m_Sprite->SetZRotation(M_PI / 2.0);
	m_Speed = E1_BASE_SPEED;
	m_Hp = E1_BASE_HP;
	m_As = E2_BASE_AS;
	//E1 move pattern
	m_MovePatern = Vector2(0, 1);
	//E1 bullet pattern
	m_BulletPatern = Vector2(0, 1);
	m_itemOdd = E2_ITEM_ODD;
}

CirclePlane::CirclePlane(float vPosition) : CirclePlane()
{
	m_Position.y = vPosition;
	int type = rand() % 2;
	switch (type)
	{
	case E2_TYPE_LEFT:
		m_Position.x = 0;
		m_MovePatern = Vector2(1, 0);
		break;
	case E2_TYPE_RIGHT:
		m_Position.x = screenWidth;
		m_MovePatern = Vector2(-1, 0);
		break;
	}
}

CirclePlane::CirclePlane(float vPosition, int type) : CirclePlane()
{
	m_Position.y = vPosition;
	switch (type)
	{
	case E2_TYPE_LEFT:
		m_Position.x = 0;
		m_MovePatern = Vector2(1, 0);
		break;
	case E2_TYPE_RIGHT:
		m_Position.x = screenWidth;
		m_MovePatern = Vector2(-1, 0);
		break;
	}
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
	//float dot = (p_Position.y - m_Position.y);
	//float det = (p_Position.x - m_Position.x);
	//float theta = atan2f(det, dot);
	//float theta = GL_Utility::GetAngle(m_Position, p_Position);
	//Vector2 p_BulletPatern = Vector2(sinf(theta), cosf(theta)) * 1.0;
	Vector2 p_BulletPatern = GL_Utility::GetMoveVector(m_Position, p_Position);
	NewBullet->SetBulletPatern(p_BulletPatern);
	NewBullet->SetBulletSpeed(E2_BULLET_SPEED);
	GameController::GetInstance()->AddEnemyBullet(NewBullet);
}
