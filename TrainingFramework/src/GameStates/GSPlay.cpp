#include "GSPlay.h"
#include <string>

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include <GameLogic\HitBox.h>

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
}

GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);


	//score game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "Score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	//score game title
	font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Hp = std::make_shared< Text>(shader, font, "Hp: 100", TEXT_COLOR::RED, 0.5);
	m_Hp->Set2DPosition(Vector2(5, screenHeight - 20));
	
	//GameController

	//GameController::GetInstance()->CreatePlayer();
	GameController::GetInstance()->CreateLevel();
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	GameController::GetInstance()->HandleKeyEvents(key, bIsPressed);
}

void GSPlay::HandleTouchEvents(int x, int y, int bIsPressed)
{
	GameController::GetInstance()->HandleTouchEvents(x, y, bIsPressed);
}

void GSPlay::Update(float deltaTime)
{
	GameController::GetInstance()->Update(deltaTime);
	std::string  score = std::to_string(GameController::GetInstance()->GetScore());
	m_score->setText("Score :" + score);
	std::string playerHp = std::to_string(GameController::GetInstance()->GetPlayerHp());
	m_Hp->setText("Hp: " + playerHp);
}

void GSPlay::Draw()
{
	GameController::GetInstance()->Draw();
	m_score->Draw();
	m_Hp->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}