#include "GSMenu.h"
#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_file.h"

#define OFFSET_H 170

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSMenu::GSMenu()
{

}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	//std::cout << MediaPlayer::GetInstance()->TestSound() << "\n";
	//std::cout << MediaPlayer::GetInstance()->PlaySound("test2.mp3") << "\n";

	//SoLoud::DiskFile* f = new SoLoud::DiskFile(MediaPlayer::GetInstance()->InitWav("test2.mp3"));
	MediaPlayer::GetInstance()->PlaySound(0);

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("Start_BTN");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 200 + OFFSET_H);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		MediaPlayer::GetInstance()->StopAllSound();
		});
	m_listButton.push_back(button);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("Exit_BTN");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 280 + OFFSET_H);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);

	//setting button
	const int middleOffset = 60;
	texture = ResourceManagers::GetInstance()->GetTexture("Settings_BTN");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 - middleOffset, 370 + OFFSET_H);
	button->SetSize(70, 70);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Option);
		});
	m_listButton.push_back(button);

	//Info button
	texture = ResourceManagers::GetInstance()->GetTexture("Info_BTN");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 + middleOffset, 370 + OFFSET_H);
	button->SetSize(70, 70);
	button->SetOnClick([]() {

		});
	m_listButton.push_back(button);

	//test animation
	//texture = ResourceManagers::GetInstance()->GetTexture("explosion");
	//shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	//m_AnimationTest = std::make_shared<AnimationSprite>(model, shader, texture, 9, 0.1f, false);
	//m_AnimationTest->Set2DPosition(100, 200);
	//m_AnimationTest->SetSize(64, 64);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("menu");
	m_Text_gameName = std::make_shared<Text>(shader, font, "Space Intruder", TEXT_COLOR::WHILE, 2.0);
	m_Text_gameName->Set2DPosition(Vector2(screenWidth / 2 - 130, 120 + OFFSET_H));
}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{

}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSMenu::HandleTouchEvents(int x, int y, int bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSMenu::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_gameName->Draw();
}
