#include "DarkPlane.h"
#include "GameLogicConfig.h"
#include "ResourceManagers.h"
#include <iostream>

void DarkPlane::Move(float delta)
{
	m_Position += Vector2(0, m_Speed * delta);
}

DarkPlane::DarkPlane()
{
	SetPosition(E1_START_POSITION);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("dark_plane");
	m_Sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_Sprite->SetSize(E1_SIZE_X, E1_SIZE_Y);
	m_Sprite->Set2DPosition(m_Position);
	m_Speed = E1_BASE_SPEED;
	m_Hp = E1_BASE_HP;
}

DarkPlane::DarkPlane(float hPosition) : DarkPlane()
{
	m_Position.x = hPosition;
}

DarkPlane::~DarkPlane()
{
}

void DarkPlane::Update(float dt)
{
	Move(dt);
	m_Sprite->Set2DPosition(m_Position);
	m_Sprite->Update(dt);
	CheckActive();
}
