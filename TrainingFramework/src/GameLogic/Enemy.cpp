#include "Enemy.h"
#include <iostream>


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

