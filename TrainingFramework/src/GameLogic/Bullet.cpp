#include "Bullet.h"
#include "GameLogicConfig.h"
#include "ResourceManagers.h"

Bullet::Bullet()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("player_bullet");
	m_Sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_Sprite->SetSize(PB_SIZE_X, PB_SIZE_Y);
	m_Sprite->Set2DPosition(m_Position);

	m_Position = Vector2(0, 0);
	m_Speed = BASE_BULLET_SPEED;
	m_BulletPatern = Vector2(0, -1);
}

Bullet::Bullet(Vector2 Position) : Bullet()
{
	m_Position = Position;
	m_Sprite->Set2DPosition(m_Position);
}

Bullet::~Bullet()
{
	std::cout << "Bullet destroyed\n";
}

void Bullet::Draw()
{
	m_Sprite->Draw();
}

void Bullet::Update(float dt)
{
	Move(dt);
	m_Sprite->Set2DPosition(m_Position);
	m_Sprite->Update(dt);
	CheckActive();
}

void Bullet::SetPosition(Vector2 Position)
{
	m_Position = Position;
}

void Bullet::SetBulletPatern(Vector2 BulletPatern)
{
	m_BulletPatern = BulletPatern;
}

void Bullet::Move(float dt)
{
	m_Position += m_BulletPatern * m_Speed * dt;
}

std::shared_ptr<Bullet> Bullet::Create(Vector2 Position)
{
	auto NewBullet = std::make_shared<Bullet>();
	NewBullet->SetPosition(Position);
	return NewBullet;
}

