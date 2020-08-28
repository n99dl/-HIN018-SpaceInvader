#include "Player.h"
#include "GameLogicConfig.h"
#include "ResourceManagers.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

void Player::Draw()
{
	m_Sprite->Draw();
}

void Player::Update(float dt)
{
	m_Sprite->Set2DPosition(m_Position);
	m_Sprite->Update(dt);
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


void Player::FixPosition()
{
	m_Position.x = max(m_Position.x, SIZE_X / 2);
	m_Position.y = max(m_Position.y, SIZE_Y / 2);
	m_Position.x = min(m_Position.x, screenWidth - SIZE_X / 2);
	m_Position.y = min(m_Position.y, screenHeight - SIZE_Y / 2);
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
	m_Speed = BASE_SPEED;
	m_Hp = BASE_HP;
}

Player::~Player()
{
}
