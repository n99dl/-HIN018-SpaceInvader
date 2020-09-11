#include "GameOverState.h"
#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_file.h"

#define OFFSET_H 300
#define LINE_WIDTH 30

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GameOverState::GameOverState()
{

}


GameOverState::~GameOverState()
{
}



void GameOverState::Init()
{
	//std::cout << MediaPlayer::GetInstance()->TestSound() << "\n";
	//std::cout << MediaPlayer::GetInstance()->PlaySound("test2.mp3") << "\n";

	//SoLoud::DiskFile* f = new SoLoud::DiskFile(MediaPlayer::GetInstance()->InitWav("test2.mp3"));
	//MediaPlayer::GetInstance()->PlaySound(0);

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//Back button
	std::shared_ptr<GameButton> button;
	const int middleOffset = 60;
	texture = ResourceManagers::GetInstance()->GetTexture("Back_BTN");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 - middleOffset, 370 + OFFSET_H);
	button->SetSize(70, 70);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);

	//Replay button
	texture = ResourceManagers::GetInstance()->GetTexture("Replay_BTN");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 + middleOffset, 370 + OFFSET_H);
	button->SetSize(70, 70);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//Highest wave
	int maxWave = GameController::GetInstance()->GetWave();
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("game_text_Bold");
	std::string highscore = "Your highest wave is " + std::to_string(maxWave);
	const char* c_stringScore = highscore.c_str();
	m_Text_notification = std::make_shared<Text>(shader, font, c_stringScore, TEXT_COLOR::BLUE, 1.2);
	m_Text_notification->Set2DPosition(Vector2(screenWidth / 2 - 150, 120));

	//Tips
	std::string tip1 = "Tips: ", tip2 = "";
	switch (maxWave)
	{
	case 0:
		tip1 +="HOW? LITERALLY, IMPOSSIBLE TO DIE";
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
		tip1 += "You did it! The universe is liberated!!";
		tip2 += "Thank you for playing!";
		break;
	}
	font = ResourceManagers::GetInstance()->GetFont("game_text");
	m_Tips_1 = std::make_shared<Text>(shader, font, tip1, TEXT_COLOR::WHILE, 0.8);
	m_Tips_1->Set2DPosition(Vector2(30, 300));	
	m_Tips_2 = std::make_shared<Text>(shader, font, tip2, TEXT_COLOR::WHILE, 0.8);
	m_Tips_2->Set2DPosition(Vector2(30 + 40, 300 + LINE_WIDTH));
}

void GameOverState::Exit()
{
}


void GameOverState::Pause()
{

}

void GameOverState::Resume()
{

}


void GameOverState::HandleEvents()
{

}

void GameOverState::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GameOverState::HandleTouchEvents(int x, int y, int bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GameOverState::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GameOverState::Draw()
{
	m_BackGround->Draw();
	m_Tips_1->Draw();
	m_Tips_2->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_notification->Draw();
}
