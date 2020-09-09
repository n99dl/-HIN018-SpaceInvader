#include "ParalelBackground.h"
#include "ResourceManagers.h"

#define MOVE_SPEED 30
#define BOTTOM 1080

ParalelBackground::ParalelBackground()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("pixel_background");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_Sprite1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_Sprite2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_Sprite1->SetSize(630, 720);
	m_Sprite2->SetSize(630, 720);
	m_Sprite2->Set2DPosition(480/2, BOTTOM);
	m_Sprite1->Set2DPosition(480/2, 720/2);
}

ParalelBackground::~ParalelBackground()
{
}


void ParalelBackground::Draw()
{
	m_Sprite1->Draw();
	m_Sprite2->Draw();
}

void ParalelBackground::Update(float dt)
{
	Vector2 MoveVector = Vector2(0, 1) * dt * MOVE_SPEED;
	Vector2 p_Sprite1 = m_Sprite1->Get2DPosition() + MoveVector;
	Vector2 p_Sprite2 = m_Sprite2->Get2DPosition() + MoveVector;
	//std::cout << "Calibrate " << m_Sprite1->Get2DPosition().y << " " << m_Sprite2->Get2DPosition().y << "\n";
	//std::cout << "Calibratex " << m_Sprite1->Get2DPosition().x << " " << m_Sprite2->Get2DPosition().x << "\n";
	if (p_Sprite1.y >= BOTTOM)
	{
		p_Sprite1.y -= 1080 + 360;
	}
	if (p_Sprite2.y >= BOTTOM)
	{
		p_Sprite2.y -= 1080 + 360;
	}
	m_Sprite1->Set2DPosition(p_Sprite1);
	m_Sprite2->Set2DPosition(p_Sprite2);
}
