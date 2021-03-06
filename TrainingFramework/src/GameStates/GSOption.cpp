#include "GSOption.h"
#include "ControllerSetting.h"
#include "Shaders.h"
#include "MediaPlayer.h"
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
#define START_POS_Y 200
#define LINE_WIDTH_Y 30
#define LEFT_BTN_X  screenWidth / 2.0 - 50
#define RIGHT_BTN_X screenWidth / 2.0 + 50

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

	//Back Button

	std::shared_ptr<GameButton> button;
	texture = ResourceManagers::GetInstance()->GetTexture("Back_BTN");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2.0, screenHeight - 100);
	button->SetSize(80, 80);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		//GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
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

	//Mouse
	texture = ResourceManagers::GetInstance()->GetTexture("Mouse_BTN");

	m_mouse = std::make_shared<GameButton>(model, shader, texture);
	m_mouse->Set2DPosition(LEFT_BTN_X, START_POS_Y + LINE_WIDTH_Y * 6.0);
	m_mouse->SetSize(50, 50);
	m_mouse->SetOnClick([]() {
		ControllerSetting::SetControlType(MOUSE);
		});
	m_listButton.push_back(m_mouse);

	//Keyboard
	texture = ResourceManagers::GetInstance()->GetTexture("Keyboard_BTN");

	m_keyboard = std::make_shared<GameButton>(model, shader, texture);
	m_keyboard->Set2DPosition(RIGHT_BTN_X, START_POS_Y + LINE_WIDTH_Y * 6.0);
	m_keyboard->SetSize(50, 50);
	m_keyboard->SetOnClick([]() {
		ControllerSetting::SetControlType(KEYBOARD);
		});
	m_listButton.push_back(m_keyboard);

	//Text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("game_text");
	auto GameText = std::make_shared<Text>(shader, font, "Sound: ", TEXT_COLOR::WHILE, 1.0);
	GameText->Set2DPosition(START_POS_X, START_POS_Y + LINE_WIDTH_Y * 0.0);
	m_listText.push_back(GameText);

	m_soundText = std::make_shared<Text>(shader, font, "ON", TEXT_COLOR::GREEN, 1.0);
	m_soundText->Set2DPosition(screenWidth / 2.0, START_POS_Y + LINE_WIDTH_Y * 0.0);
	m_listText.push_back(m_soundText);

	GameText = std::make_shared<Text>(shader, font, "Control type: ", TEXT_COLOR::WHILE, 1.0);
	GameText->Set2DPosition(START_POS_X, START_POS_Y + LINE_WIDTH_Y * 4.0);
	m_listText.push_back(GameText);

	m_controlTypeText = std::make_shared<Text>(shader, font, "MOUSE", TEXT_COLOR::GREEN, 1.0);
	m_controlTypeText->Set2DPosition(screenWidth / 2.0, START_POS_Y + LINE_WIDTH_Y * 4.0);
	m_listText.push_back(m_controlTypeText);
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
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSOption::Update(float deltaTime)
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
	int ControlType = ControllerSetting::GetControlType();
	if (ControlType == MOUSE)
	{
		m_controlTypeText->SetColor(m_controlTypeText->EnumToVector(TEXT_COLOR::CYAN));
		m_controlTypeText->setText("Mouse");
	}
	else
	{
		m_controlTypeText->SetColor(m_controlTypeText->EnumToVector(TEXT_COLOR::BLUE));
		m_controlTypeText->setText("Keyboard");
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

void GSOption::Draw()
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

void GSOption::SetStateMuteBtn()
{
	
}
