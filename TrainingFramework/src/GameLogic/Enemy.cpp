#include "Enemy.h"
#include <iostream>

void Enemy::CheckActive()
{
	if (m_Hp <= 0)
		m_isActive = false;
	if (Entity::OutOfWindow(m_Position))
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
	m_Sprite->Set2DPosition(m_Position);
	m_Sprite->Update(dt);
}

void Enemy::SetPosition(Vector2 Position)
{
	m_Position = Position;
}

bool Enemy::isActive()
{
	return m_isActive;
}
