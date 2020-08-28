#include "GSIntro.h"
#define DELAY_TIME 2


extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

class Text;


GSIntro::GSIntro()
{
	m_time = 0;
}


GSIntro::~GSIntro()
{
}


void GSIntro::Init()
{
	// background
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_logo");

	m_bg = std::make_shared<Sprite2D>(model, shader, texture);
	m_bg->SetSize(screenWidth, screenHeight);

	//loading
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_loading = std::make_shared< Text>(shader, font, "loading...", TEXT_COLOR::WHILE, 1.0);
	m_Text_loading->Set2DPosition(Vector2(screenWidth/2 - 40, screenHeight - 30));
}

void GSIntro::Exit()
{
	
}


void GSIntro::Pause()
{
	
}

void GSIntro::Resume()
{
	
}


void GSIntro::HandleEvents()
{
	
}

void GSIntro::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSIntro::HandleTouchEvents(int x, int y, int bIsPressed)
{

}

void GSIntro::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > DELAY_TIME)
	{
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		m_time = 0;
	}
}

void GSIntro::Draw()
{
	m_bg->Draw();
	m_Text_loading->Draw();
}
