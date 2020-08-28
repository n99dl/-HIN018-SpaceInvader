#include "GSOption.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSOption::GSOption()
{
}

GSOption::~GSOption()
{
}

void GSOption::Init()
{
	std::cout << "Enter option scene";
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);
}

void GSOption::Exit()
{
}

void GSOption::Pause()
{
}

void GSOption::Resume()
{
}

void GSOption::HandleEvents()
{
}

void GSOption::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSOption::HandleTouchEvents(int x, int y, int bIsPressed)
{
}

void GSOption::Update(float deltaTime)
{
}

void GSOption::Draw()
{
	m_BackGround->Draw();
}
