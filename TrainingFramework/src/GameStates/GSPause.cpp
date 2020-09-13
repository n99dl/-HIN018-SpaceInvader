#include "GSPause.h"
#include "Shaders.h"
#include "MediaPlayer.h"
#include "Gamelogic/GameController.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

#define START_POS_X 50
#define START_POS_Y 100
#define LINE_WIDTH_Y 30
#define LEFT_BTN_X  screenWidth / 2.0 - 50
#define RIGHT_BTN_X screenWidth / 2.0 + 50

GSPause::GSPause()
{
}

GSPause::~GSPause()
{
}

void GSPause::Init()
{
	std::cout << "Enter option scene";
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//Back Button

	std::shared_ptr<GameButton> button;
	texture = ResourceManagers::GetInstance()->GetTexture("Back_BTN");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2.0 - 50, screenHeight - 100);
	button->SetSize(70, 70);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);

	texture = ResourceManagers::GetInstance()->GetTexture("Menu_BTN");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2.0 + 50, screenHeight - 100);
	button->SetSize(70, 70);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->Cleanup();
		GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);

	//Mute Button
	m_isMute = MediaPlayer::GetInstance()->IsMute();
	texture = ResourceManagers::GetInstance()->GetTexture("Sound_BTN");

	m_mute = std::make_shared<GameButton>(model, shader, texture);
	m_mute->Set2DPosition(LEFT_BTN_X, START_POS_Y + LINE_WIDTH_Y * 2.0);
	m_mute->SetSize(50, 50);
	m_mute->SetOnClick([]() {
		MediaPlayer::GetInstance()->Mute();
		});
	m_listButton.push_back(m_mute);

	//unmute
	texture = ResourceManagers::GetInstance()->GetTexture("Sound_BTN_active");

	m_unmute = std::make_shared<GameButton>(model, shader, texture);
	m_unmute->Set2DPosition(RIGHT_BTN_X, START_POS_Y + LINE_WIDTH_Y * 2.0);
	m_unmute->SetSize(50, 50);
	m_unmute->SetOnClick([]() {
		MediaPlayer::GetInstance()->UnMute();
		});
	m_listButton.push_back(m_unmute);

	//Text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("game_text");
	auto GameText = std::make_shared<Text>(shader, font, "Sound: ", TEXT_COLOR::WHILE, 1.0);
	GameText->Set2DPosition(START_POS_X, START_POS_Y + LINE_WIDTH_Y * 0.0);
	m_listText.push_back(GameText);

	m_soundText = std::make_shared<Text>(shader, font, "ON", TEXT_COLOR::GREEN, 1.0);
	m_soundText->Set2DPosition(START_POS_X + 100, START_POS_Y + LINE_WIDTH_Y * 0.0);
	m_listText.push_back(m_soundText);

	//Tips
	int maxWave = GameController::GetInstance()->GetWave();
	std::string tip1 = "Tips: ", tip2 = "";
	switch (maxWave)
	{
	case 0:
		tip1 += "Liberate the Universe Sergant.";
		tip2 += "The whole universe lie on your...controller!";
		break;
	case 1:
		tip1 += "Enemy BULLET will injured you, noobs";
		tip2 = "HIT the ENEMY also damage you";
		break;
	case 2:
		tip1 += "Circle plane will AIM for your POSITION.";
		tip2 = "Try MOVING around continously";
		break;
	case 3:
		tip1 += "DESTROY formation quickly";
		tip2 = "Collect more POWER UP!";
		break;
	case 4:
		tip1 += "Motor use HOMING bullet";
		tip2 = "Try to lure the bullet out of the screen";
		break;
	case 5:
		tip1 += "Move through the GAP of the MINIGUN.";
		tip2 = "You can do it!";
		break;
	case 6:
		tip1 += "You did it! The universe is Destroyed!!";
		tip2 += "Yes, you are the Intruder! Not them! Ha";
		break;
	}
	font = ResourceManagers::GetInstance()->GetFont("game_text");
	m_Tips_1 = std::make_shared<Text>(shader, font, tip1, TEXT_COLOR::WHILE, 0.8);
	m_Tips_1->Set2DPosition(Vector2(START_POS_X,		START_POS_Y + LINE_WIDTH_Y * 10.0));
	m_Tips_2 = std::make_shared<Text>(shader, font, tip2, TEXT_COLOR::WHILE, 0.8);
	m_Tips_2->Set2DPosition(Vector2(START_POS_X + 40,	START_POS_Y + LINE_WIDTH_Y * 11.0));
	m_listText.push_back(m_Tips_1);
	m_listText.push_back(m_Tips_2);
}

void GSPause::Exit()
{
}

void GSPause::Pause()
{
}

void GSPause::Resume()
{
}

void GSPause::HandleEvents()
{
}

void GSPause::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSPause::HandleTouchEvents(int x, int y, int bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPause::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	SetStateMuteBtn();
	bool isMute = MediaPlayer::GetInstance()->IsMute();
	if (isMute != m_isMute)
	{
		m_isMute = isMute;
		if (m_isMute)
		{
			m_soundText->SetColor(m_soundText->EnumToVector(TEXT_COLOR::RED));
			m_soundText->setText("OFF");
		}
		else
		{
			m_soundText->SetColor(m_soundText->EnumToVector(TEXT_COLOR::GREEN));
			m_soundText->setText("ON");
		}
	}
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listText)
	{
		it->Update(deltaTime);
	}
}

void GSPause::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}
}

void GSPause::SetStateMuteBtn()
{

}
