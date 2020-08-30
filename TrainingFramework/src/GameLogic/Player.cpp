#include "Player.h"
#include "GameLogicConfig.h"
#include "ResourceManagers.h"
#include <GameLogic\Bullet.h>
#include <GameLogic\GameController.h>

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

void Player::Draw()
{
	m_Sprite->Draw();
}

void Player::Update(float dt)
{
	if (m_IsShooting)
		Shoot();
	m_Sprite->Set2DPosition(m_Position);
	m_Sprite->Update(dt);
	m_HitBox->SetPosition(m_Position);
	m_ShootTime += dt;
	m_ShootTime = min(m_ShootTime, m_AttackSpeed);
}

void Player::Move(int KeyPressed, float dt)
{
	Vector2 NewPosition = Vector2(0, 0);
	if (KeyPressed & MOVE_UP)
		NewPosition += Vector2(0, -1);
	if (KeyPressed & MOVE_DOWN)
		NewPosition += Vector2(0, 1);
	if (KeyPressed & MOVE_LEFT)
		NewPosition += Vector2(-1, 0);
	if (KeyPressed & MOVE_RIGHT)
		NewPosition += Vector2(1, 0);
	NewPosition *= dt * m_Speed;
	m_Position += NewPosition;
	FixPosition();
}

void Player::MoveByMouse(int x, int y)
{
	m_Position = Vector2(x, y);
	FixPosition();
}

void Player::Shoot()
{
	if (m_ShootTime < m_AttackSpeed)
	{
		return;
	}
	else
		m_ShootTime -= m_AttackSpeed;
	switch (m_WeaponLevel)
	{
	case 1:
		ShootStraight();
		break;
	case 2:
		ShootDouble();
		break;
	case 3:
		ShootDouble();
		ShootRear();
	default:
		break;
	}
}

void Player::SetIsShooting(bool IsShooting)
{
	m_IsShooting = IsShooting;
}

void Player::PowerUp()
{
	if (m_WeaponLevel < 3)
		m_WeaponLevel++;
	else if (m_AttackSpeed > 0.1)
		m_AttackSpeed -= 0.05;
}

void Player::ConsumeItem(std::shared_ptr<Item> _Item)
{
	switch (_Item->GetType())
	{
	case ITEM_POWER_UP:
		PowerUp();
		break;
	default:
		break;
	}
}


void Player::FixPosition()
{
	m_Position.x = max(m_Position.x, SIZE_X / 2);
	m_Position.y = max(m_Position.y, SIZE_Y / 2);
	m_Position.x = min(m_Position.x, screenWidth - SIZE_X / 2);
	m_Position.y = min(m_Position.y, screenHeight - SIZE_Y / 2);
}

void Player::ShootStraight()
{
	//std::shared_ptr<Bullet> NewBullet = Bullet::Create(m_Position);
	//GameController::GetInstance()->AddBullet(NewBullet);
	std::shared_ptr<Bullet> NewBullet = std::make_shared<Bullet>(m_Position);
	GameController::GetInstance()->AddBullet(NewBullet);
}

void Player::ShootDouble()
{
	Vector2 bulletPosition = m_Position;
	bulletPosition += Vector2(-DOUBLE_SHOOT_OFFSET, 0); //Fix Offset for now
	std::shared_ptr<Bullet> NewBullet = std::make_shared<Bullet>(bulletPosition);
	GameController::GetInstance()->AddBullet(NewBullet);

	bulletPosition += Vector2(DOUBLE_SHOOT_OFFSET, 0) * 2; //Fix Offset for now
	std::shared_ptr<Bullet> NewBullet2 = std::make_shared<Bullet>(bulletPosition);
	GameController::GetInstance()->AddBullet(NewBullet2);
}

void Player::ShootRear()
{
	Vector2 bulletPosition = m_Position;
	bulletPosition += Vector2(-REAR_SHOOT_OFFSET, 0); //Fix Offset for now
	std::shared_ptr<Bullet> NewBullet = std::make_shared<Bullet>(bulletPosition);
	NewBullet->SetBulletPatern(Vector2(-0.2, -1)); // Left
	GameController::GetInstance()->AddBullet(NewBullet);

	bulletPosition += Vector2(REAR_SHOOT_OFFSET, 0) * 2; //Fix Offset for now
	std::shared_ptr<Bullet> NewBullet2 = std::make_shared<Bullet>(bulletPosition);
	NewBullet2->SetBulletPatern(Vector2(0.2, -1)); // Right
	GameController::GetInstance()->AddBullet(NewBullet2);
}

Player::Player()
{
	m_Position = START_POSITION;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("plane_blue");
	m_Sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_Sprite->SetSize(SIZE_X, SIZE_Y);
	m_Sprite->Set2DPosition(m_Position);
	m_HitBox = std::make_shared<HitBox>(Vector2(m_Position), Vector2(SIZE_X / 2.0 - 5, SIZE_Y / 2.0 - 5));
	m_Speed = BASE_SPEED;
	m_Hp = BASE_HP;
	m_WeaponLevel = BASE_WEAPON_POWER;
	m_ShootTime = 0;
	m_IsShooting = 0;
	m_AttackSpeed = BASE_ATTACK_SPEED;
	std::cout << "As :" << m_AttackSpeed << "\n";
}

Player::~Player()
{
}
