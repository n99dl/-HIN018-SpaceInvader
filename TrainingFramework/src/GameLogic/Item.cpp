#include "Item.h"
#include <iostream>
#include <time.h>

Item::Item()
{
	m_Type = 0;
	m_Position = Vector2(0, 0);
	m_Speed = ITEM_SPEED;
	m_MovePatern = Vector2(0, 1);
}

Item::Item(int type, Vector2 Position) : Item()
{
	m_Type = type;
	m_Position = Position;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	std::shared_ptr<Texture> texture;
	switch (m_Type)
	{
	case ITEM_POWER_UP:
		texture = ResourceManagers::GetInstance()->GetTexture("item_power_up");
		break;
	case ITEM_HEATH:
		texture = ResourceManagers::GetInstance()->GetTexture("item_heath");
		break;
	default:
		texture = ResourceManagers::GetInstance()->GetTexture("logo");
		break;
	}
	m_Sprite = std::make_shared<Sprite2D>(model, shader, texture);
	m_Sprite->SetSize(ITEM_SIZE_X, ITEM_SIZE_Y);
	m_Sprite->Set2DPosition(m_Position);
	m_HitBox = std::make_shared<HitBox>(Vector2(m_Position), Vector2(ITEM_SIZE_X / 2.0 - 5, ITEM_SIZE_Y / 2.0 - 5));
	m_MovePatern = Vector2(0.5, 1);
	srand(time(NULL));
	int odd = rand() % 2;
	if (odd)
		m_MovePatern.x = -m_MovePatern.x;
}

void Item::Draw()
{
	m_Sprite->Draw();
}

void Item::Update(float dt)
{
	Move(dt);
	m_Sprite->Set2DPosition(m_Position);
	m_Sprite->Update(dt);
	m_HitBox->SetPosition(m_Position);
	CheckActive();
}

void Item::Move(float dt)
{
	m_Position += m_MovePatern * m_Speed * dt;
}

void Item::Destroy()
{
	m_isActive = false;
}

int Item::GetType()
{
	return m_Type;
}

Item::~Item()
{
}
