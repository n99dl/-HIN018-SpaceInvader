#include "GSPlay.h"
#include <string>

#include "ControllerSetting.h"
#include "MediaPlayer.h"
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
	std::cout << "Exit play\n";
}


void GSPlay::Init()
{
	if (ControllerSetting::GetControlType() == MOUSE)
	{
		ShowCursor(false);
	}
	MediaPlayer::GetInstance()->PlaySound(PLAY_MUSIC_ID);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//Foreground

	m_Foreground = std::make_shared<Foreground>();
	
	//GameController
	GameController::FreeInstance();
	GameController::GetInstance()->CreateLevel();

	m_frames = 0;
	m_totalFrameTime = 0.0;
}

void GSPlay::Exit()
{
	ShowCursor(true);
}


void GSPlay::Pause()
{
	
}

void GSPlay::Resume()
{
	if (ControllerSetting::GetControlType() == MOUSE)
	{
		ShowCursor(false);
	}
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
	//m_frames++;
	//m_totalFrameTime += deltaTime;
	//if (m_frames >= 3)
	//{
	//	std::cout << "Fps :" << (float)m_frames / m_totalFrameTime << "\n";
	//	m_frames = 0;
	//	m_totalFrameTime = 0;
	//}
	GameController::GetInstance()->Update(deltaTime);
	std::string  score = std::to_string(GameController::GetInstance()->GetScore());
	//m_score->setText("Score :" + score);
	std::string playerHp = std::to_string(GameController::GetInstance()->GetPlayerHp());
	m_Foreground->Update(deltaTime);
	//m_Hp->setText("Hp: " + playerHp);
}

void GSPlay::Draw()
{
	GameController::GetInstance()->Draw();
	m_Foreground->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}