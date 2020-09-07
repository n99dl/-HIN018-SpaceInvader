#include "Bullet.h"
#include "GameLogicConfig.h"
#include "ResourceManagers.h"
#include "GameController.h"
#include <GameLogic\GL_Utility.h>

void Bullet::ReCalculateBulletPatern()
{
	Vector2 p_Position = GameController::GetInstance()->GetPlayerPosition();
	Vector2 p_BulletPatern = GL_Utility::GetMoveVector(m_Position, p_Position);
	p_BulletPatern = (p_BulletPatern + m_BulletPatern * 9.0) / 10.0;
	m_BulletPatern = p_BulletPatern;
}

Bullet::Bullet()
{
	m_Position = Vector2(0, 0);
	m_Speed = BASE_BULLET_SPEED;
	m_Power = BASE_BULLET_POWER;
	m_BulletPatern = Vector2(0, -1); //Move Upward
	m_IsHoming = false;
	m_HomingCooldown = 0.0f;
}
Bullet::Bullet(int type) : Bullet()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	std::shared_ptr<Texture> texture;
	int xSize = 0, ySize = 0;
	switch (type)
	{
	case PLAYER_BULLET:
		texture = ResourceManagers::GetInstance()->GetTexture("player_bullet");
		m_HitBox = std::make_shared<HitBox>(Vector2(m_Position), Vector2(PB_SIZE_X / 2.0 - 10, PB_SIZE_Y / 2.0 - 5));
		xSize = PB_SIZE_X;
		ySize = PB_SIZE_Y;
		break;
	case E1_BULLET:
		texture = ResourceManagers::GetInstance()->GetTexture("enemy_bullet");
		m_HitBox = std::make_shared<HitBox>(Vector2(m_Position), Vector2(E1B_SIZE_X / 2.0 - 5, E1B_SIZE_Y / 2.0 - 5));
		xSize = E1B_SIZE_X;
		ySize = E1B_SIZE_Y;
		break;
	case E3_BULLET:
		texture = ResourceManagers::GetInstance()->GetTexture("enemy_bullet");
		m_HitBox = std::make_shared<HitBox>(Vector2(m_Position), Vector2(E1B_SIZE_X / 2.0 - 5, E1B_SIZE_Y / 2.0 - 5));
		xSize = E1B_SIZE_X;
		ySize = E1B_SIZE_Y;
		m_Power = E3_BULLET_POWER;
		m_BulletPatern = Vector2(0, 1);
		EnableHoming();
		break;
	default:
		break;
	}
	m_Sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_Sprite->SetSize(xSize, ySize);
	m_Sprite->Set2DPosition(m_Position);
}

Bullet::Bullet(Vector2 Position, int type) : Bullet(type)
{
	m_Position = Position;
	m_Sprite->Set2DPosition(m_Position);
	m_HitBox->SetPosition(Position);
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
	if (m_IsHoming)
	{
		if (m_HomingCooldown <= 0)
		{
			ReCalculateBulletPatern();
			m_HomingCooldown += HOMING_COOLDOWN;
		}
		else
			m_HomingCooldown -= dt;
	}
	Move(dt);
	m_Sprite->Set2DPosition(m_Position);
	m_Sprite->Update(dt);
	m_HitBox->SetPosition(m_Position);
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

void Bullet::SetBulletSpeed(int Speed)
{
	m_Speed = Speed;
}

void Bullet::Move(float dt)
{
	m_Position += m_BulletPatern * m_Speed * dt;
}

void Bullet::EnableHoming()
{
	m_IsHoming = true;
}

int Bullet::GetPower()
{
	return m_Power;
}

void Bullet::SelfDestruct()
{
	m_isActive = false;
}

std::shared_ptr<Bullet> Bullet::Create(Vector2 Position)
{
	auto NewBullet = std::make_shared<Bullet>();
	NewBullet->SetPosition(Position);
	return NewBullet;
}

