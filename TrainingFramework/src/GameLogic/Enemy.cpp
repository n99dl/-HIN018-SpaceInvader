#include "Enemy.h"
#include <iostream>
#include <GameLogic\Bullet.h>


void Enemy::CheckAlive()
{
	if (m_Hp <= 0)
		m_isActive = false;
}

Enemy::Enemy()
{
	std::cout << "Enemy created\n";
	m_isActive = true;
}

Enemy::Enemy(Vector2 Position)
{
	SetPosition(Position);
}

Enemy::~Enemy()
{
}

void Enemy::Draw()
{
	m_Sprite->Draw();
}

void Enemy::Update(float dt)
{
	Move(dt);
	m_Sprite->Set2DPosition(m_Position);
	m_Sprite->Update(dt);
	m_HitBox->SetPosition(m_Position);
	CheckAlive();
}

void Enemy::SetPosition(Vector2 Position)
{
	m_Position = Position;
}

void Enemy::Move(float delta)
{
	m_Position += Vector2(0, m_Speed * delta);
}

void Enemy::DamageBy(std::shared_ptr<Bullet> _Bullet)
{
	if (!_Bullet->isActive())
		return;
	std::cout << "Get shot by " << _Bullet->GetID() << "\n";
	m_Hp -= _Bullet->GetPower();
}

