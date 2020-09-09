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
	int odd = rand() % m_itemOdd; //Let Fix value for now
	auto texture = ResourceManagers::GetInstance()->GetTexture("red_explosion");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader"); 
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	std::shared_ptr<AnimationSprite> Explosion = std::make_shared<AnimationSprite>(model, shader, texture, RE_NUM_FRAME, RE_FRAME_TIME, false);
	Explosion->Set2DPosition(m_Position);
	Explosion->SetSize(RE_SIZE, RE_SIZE);
	GameController::GetInstance()->AddAnimation(Explosion);
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
	m_MovePatern = Vector2(0, 1);
	srand(time(NULL));
	float random = rand() % 20;
	m_currentTime = 0.1f * random;
	m_itemOdd = 10;
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
	m_currentTime += dt;
	if (m_currentTime >= m_As)
	{
		Shoot();
		m_currentTime -= m_As;
	}
}

void Enemy::SetPosition(Vector2 Position)
{
	m_Position = Position;
}

void Enemy::Move(float delta)
{
	m_Position += m_MovePatern * delta * m_Speed;
}

void Enemy::DamageBy(std::shared_ptr<Bullet> _Bullet)
{
	if (!_Bullet->isActive())
		return;
	std::cout << "Get shot by " << _Bullet->GetID() << "\n";
	m_Hp -= _Bullet->GetPower();
	//impact effect
	auto texture = ResourceManagers::GetInstance()->GetTexture("impact");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	std::shared_ptr<AnimationSprite> impactAnimation = std::make_shared<AnimationSprite>(model, shader, texture, I_NUM_FRAME, I_FRAME_TIME, false);
	impactAnimation->Set2DPosition(_Bullet->GetPosition());
	impactAnimation->SetSize(I_SIZE, I_SIZE);
	GameController::GetInstance()->AddAnimation(impactAnimation);
}

void Enemy::Shoot()
{
	std::cout << "Enemy class shoot\n";
}

