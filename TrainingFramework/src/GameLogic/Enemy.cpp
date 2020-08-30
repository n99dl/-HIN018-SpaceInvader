#include "Enemy.h"
#include <iostream>
#include <GameLogic\Bullet.h>
#include <time.h>
#include <GameLogic\Item.h>
#include <GameLogic\GameController.h>


void Enemy::CheckAlive()
{
	if (m_Hp <= 0)
	{
		Die();
	}
}

void Enemy::Die()
{
	m_isActive = false;
	srand(time(NULL));
	int odd = rand() % 4; //Let Fix value for now
	if (!odd)
	DropItem();
}

void Enemy::DropItem()
{
	srand(time(NULL));
	int type = rand() % 2 + 1;
	auto NewItem = std::make_shared<Item>(type, m_Position);
	GameController::GetInstance()->AddItem(NewItem);
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

