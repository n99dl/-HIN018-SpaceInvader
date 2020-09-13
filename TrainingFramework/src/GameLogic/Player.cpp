#include "Player.h"
#include "GameLogicConfig.h"
#include "ResourceManagers.h"
#include <GameLogic\Bullet.h>
#include <GameLogic\GameController.h>
#include "MediaPlayer.h"

#define STRAIGHT 0
#define LEAN_LEFT 1
#define LEAN_RIGHT 2

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

void Player::Draw()
{
	m_Sprite->Draw();
}

void Player::Update(float dt)
{
	if (!m_isActive) return;
	if (m_IsShooting)
		Shoot();
	Vector2 OldPosition = m_Sprite->Get2DPosition();
	m_leanCooldown -= dt;
	m_leanCooldown = max(m_leanCooldown, 0.0f);
	if (m_Position.x - OldPosition.x > 0.0f)
	{
		if (m_spriteState != LEAN_RIGHT)
		{
			LeanRight();
			m_spriteState = LEAN_RIGHT;
		}
		m_leanCooldown = 0.1f;
	} else
		if (m_Position.x - OldPosition.x < -0.0f)
		{
			if (m_spriteState != LEAN_LEFT)
			{
				LeanLeft();
				m_spriteState = LEAN_LEFT;
			}
			m_leanCooldown = 0.1f;
		}
		else
			if (m_spriteState != STRAIGHT && m_leanCooldown == 0.0f)
			{
				BackStraight();
				m_spriteState = STRAIGHT;
			}

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
	MediaPlayer::GetInstance()->PlaySound(PLAYER_SHOOT_ID);
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
		break;
	case 4:
		ShootStraight();
		ShootDouble();
		ShootRear();
		break;
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
	if (m_WeaponLevel < 4)
	{
		m_WeaponLevel++;
		m_totalPower++;
	}
	else if (m_AttackSpeed > 0.2)
	{
		m_AttackSpeed -= 0.05;
		m_totalPower++;
	}
	else if (m_bulletPower <= 13)
	{
		std::cout << "Empowering\n";
		m_bulletType = EMPOWERED_P_BULLET;
		m_bulletPower+=2;
		m_totalPower++;
	}
	MediaPlayer::GetInstance()->PlaySound(POWER_UP_ID);
}

void Player::HpUp()
{
	m_Hp += 20;
	MediaPlayer::GetInstance()->PlaySound(POWER_UP_ID);
	MediaPlayer::GetInstance()->PlaySound(HP_UP);
	m_Hp = min(m_Hp, 110);
}

void Player::ConsumeItem(std::shared_ptr<Item> _Item)
{
	switch (_Item->GetType())
	{
	case ITEM_POWER_UP:
		PowerUp();
		break;
	default:
		HpUp();
		break;
	}
}

void Player::DamageBy(std::shared_ptr<Bullet> _Bullet)
{
	if (!_Bullet->isActive())
		return;
	//std::cout << "Get shot by " << _Bullet->GetID() << "\n";
	m_Hp -= _Bullet->GetPower();
	//impact effect
	auto texture = ResourceManagers::GetInstance()->GetTexture("impact");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	std::shared_ptr<AnimationSprite> impactAnimation = std::make_shared<AnimationSprite>(model, shader, texture, I_NUM_FRAME, I_FRAME_TIME, false);
	impactAnimation->Set2DPosition(_Bullet->GetPosition());
	impactAnimation->SetSize(P_I_SIZE, P_I_SIZE);
	GameController::GetInstance()->AddAnimation(impactAnimation);
	MediaPlayer::GetInstance()->PlaySound(PLAYER_HIT);
	if (m_Hp <= 0)
	{
		Die();
	}
}

void Player::DamageBy(std::shared_ptr<Enemy> _Enemy)
{
	if (!_Enemy->isActive())
		return;
	//std::cout << "Collide with " << _Enemy->GetID() << "\n";
	m_Hp -= _Enemy->getHp();
	//impact effect
	auto texture = ResourceManagers::GetInstance()->GetTexture("impact");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	std::shared_ptr<AnimationSprite> impactAnimation = std::make_shared<AnimationSprite>(model, shader, texture, I_NUM_FRAME, I_FRAME_TIME, false);
	impactAnimation->Set2DPosition(_Enemy->GetPosition());
	impactAnimation->SetSize(I_SIZE, I_SIZE);
	GameController::GetInstance()->AddAnimation(impactAnimation);
	MediaPlayer::GetInstance()->PlaySound(PLAYER_HIT);
	if (m_Hp <= 0)
	{
		Die();
	}
	else
	{
		_Enemy->InstaDie();
	}
}

int Player::GetHp()
{
	return m_Hp;
}

int Player::GetPower()
{
	return m_totalPower;
}

void Player::HackBulletPower()
{
	m_bulletPower = 9001;
}

int Player::GetBulletPower()
{
	return m_bulletPower;
}

void Player::Die()
{
	m_isActive = false;
	m_Sprite->Set2DPosition(-100, -100);
	auto texture = ResourceManagers::GetInstance()->GetTexture("blue_explosion");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	std::shared_ptr<AnimationSprite> Explosion = std::make_shared<AnimationSprite>(model, shader, texture, BE_NUM_FRAME, BE_FRAME_TIME, true);
	Explosion->Set2DPosition(m_Position);
	Explosion->SetSize(BE_SIZE, BE_SIZE);
	MediaPlayer::GetInstance()->StopSound(PLAY_MUSIC_ID);
	MediaPlayer::GetInstance()->PlaySound(PLAYER_DEAD);
	GameController::GetInstance()->AddAnimation(Explosion);
	GameController::GetInstance()->StartGameOverCountDown();
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
	//std::shared_ptr<Bullet> NewBullet = std::make_shared<Bullet>(m_Position, PLAYER_BULLET);
	std::shared_ptr<Bullet> NewBullet = ObjectPools::GetInstance()->getPlayerBullet();
	NewBullet->InitBulletWithTypeAndPosition(m_Position, m_bulletType);
	NewBullet->SetBulletPatern(Vector2(0, -1));
	GameController::GetInstance()->AddPlayerBullet(NewBullet);
}

void Player::ShootDouble()
{
	Vector2 bulletPosition = m_Position;
	bulletPosition += Vector2(-DOUBLE_SHOOT_OFFSET, 0); //Fix Offset for now

	std::shared_ptr<Bullet> NewBullet = ObjectPools::GetInstance()->getPlayerBullet();
	NewBullet->InitBulletWithTypeAndPosition(bulletPosition, m_bulletType);
	NewBullet->SetBulletPatern(Vector2(0, -1));
	GameController::GetInstance()->AddPlayerBullet(NewBullet);

	//std::shared_ptr<Bullet> NewBullet = std::make_shared<Bullet>(bulletPosition, PLAYER_BULLET);
	//GameController::GetInstance()->AddPlayerBullet(NewBullet);

	bulletPosition += Vector2(DOUBLE_SHOOT_OFFSET, 0) * 2; //Fix Offset for now
	//std::shared_ptr<Bullet> NewBullet2 = std::make_shared<Bullet>(bulletPosition, PLAYER_BULLET);
	//GameController::GetInstance()->AddPlayerBullet(NewBullet2);
	NewBullet = ObjectPools::GetInstance()->getPlayerBullet();
	NewBullet->InitBulletWithTypeAndPosition(bulletPosition, m_bulletType);
	NewBullet->SetBulletPatern(Vector2(0, -1));
	GameController::GetInstance()->AddPlayerBullet(NewBullet);
}

void Player::ShootRear()
{
	Vector2 bulletPosition = m_Position;
	bulletPosition += Vector2(-REAR_SHOOT_OFFSET, 0); //Fix Offset for now
	//std::shared_ptr<Bullet> NewBullet = std::make_shared<Bullet>(bulletPosition, PLAYER_BULLET);
	//NewBullet->SetBulletPatern(Vector2(-0.2, -1)); // Left
	//GameController::GetInstance()->AddPlayerBullet(NewBullet);

	std::shared_ptr<Bullet> NewBullet = ObjectPools::GetInstance()->getPlayerBullet();
	NewBullet->InitBulletWithTypeAndPosition(bulletPosition, m_bulletType);
	NewBullet->SetBulletPatern(Vector2(-0.2, -1)); // Left
	GameController::GetInstance()->AddPlayerBullet(NewBullet);

	bulletPosition += Vector2(REAR_SHOOT_OFFSET, 0) * 2; //Fix Offset for now
	//std::shared_ptr<Bullet> NewBullet2 = std::make_shared<Bullet>(bulletPosition, PLAYER_BULLET);
	NewBullet = ObjectPools::GetInstance()->getPlayerBullet();
	NewBullet->InitBulletWithTypeAndPosition(bulletPosition, m_bulletType);
	NewBullet->SetBulletPatern(Vector2(0.2, -1)); // Right
	GameController::GetInstance()->AddPlayerBullet(NewBullet);
}

void Player::LeanLeft()
{
	//std::cout << "Lean left\n";
	m_Sprite = m_leftSprite;
}

void Player::LeanRight()
{
	//std::cout << "Lean Right\n";
	m_Sprite = m_rightSprite;
}

void Player::BackStraight()
{
	m_Sprite = m_straightSprite;
}

Player::Player()
{
	m_Position = START_POSITION;
	//Base sprite
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	//auto texture = ResourceManagers::GetInstance()->GetTexture("plane_blue");
	auto texture = ResourceManagers::GetInstance()->GetTexture("plane_blue");
	m_straightSprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_straightSprite->SetSize(SIZE_X, SIZE_Y);

	//Lean Left
	//texture = ResourceManagers::GetInstance()->GetTexture("player_lean_left");
	texture = ResourceManagers::GetInstance()->GetTexture("player_left");
	m_leftSprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_leftSprite->SetSize(SIZE_X, SIZE_Y);

	// lean right
	//texture = ResourceManagers::GetInstance()->GetTexture("player_lean_right");
	texture = ResourceManagers::GetInstance()->GetTexture("player_right");
	m_rightSprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_rightSprite->SetSize(SIZE_X, SIZE_Y);

	m_Sprite = m_straightSprite;
	m_Sprite->Set2DPosition(m_Position);

	m_HitBox = std::make_shared<HitBox>(Vector2(m_Position), 
		Vector2(SIZE_X / 2.0 - P_HITBOX_OFFSET_X, 
				SIZE_Y / 2.0 - P_HITBOX_OFFSET_Y));
	m_Speed = BASE_SPEED;
	m_Hp = BASE_HP;
	m_WeaponLevel = BASE_WEAPON_POWER;
	m_ShootTime = 0;
	m_IsShooting = 0;
	m_AttackSpeed = BASE_ATTACK_SPEED;
	m_spriteState = STRAIGHT;
	m_leanCooldown = 0;
	m_bulletPower = 10;
	m_totalPower = 1;
	m_bulletType = PLAYER_BULLET;
	//std::cout << "As :" << m_AttackSpeed << "\n";
}

Player::~Player()
{
}
