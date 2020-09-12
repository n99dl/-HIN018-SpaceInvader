#include "GSInfo.h"
#include "Text.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

#define START_POS_X 20
#define START_POS_Y 100
#define LINE_WIDTH_Y 40
#define LEFT_BTN_X  screenWidth / 2.0 - 50
#define RIGHT_BTN_X screenWidth / 2.0 + 50

GSInfo::GSInfo()
{
}

GSInfo::~GSInfo()
{
}

void GSInfo::Init()
{
	std::cout << "Enter Info scene\n";
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BG");
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

	float textSize = 0.8f;
	float line = 0.0f;
	//Text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("game_text");
	auto GameText = std::make_shared<Text>(shader, font, "Hello Sergant! Your mission is liberate the universe. ", TEXT_COLOR::WHILE, textSize);
	GameText->Set2DPosition(START_POS_X, START_POS_Y + LINE_WIDTH_Y * line);
	line++;
	m_listText.push_back(GameText);

	GameText = std::make_shared<Text>(shader, font, "Destroy the enemy while dodging incoming attack. ", TEXT_COLOR::WHILE, textSize);
	GameText->Set2DPosition(START_POS_X, START_POS_Y + LINE_WIDTH_Y * line);
	line++;
	m_listText.push_back(GameText);

	GameText = std::make_shared<Text>(shader, font, "Collect power up and assassinate the Imperial!", TEXT_COLOR::WHILE, textSize);
	GameText->Set2DPosition(START_POS_X, START_POS_Y + LINE_WIDTH_Y * line);
	line++;
	m_listText.push_back(GameText);

	GameText = std::make_shared<Text>(shader, font, "Good luck my soldier!", TEXT_COLOR::WHILE, textSize);
	GameText->Set2DPosition(START_POS_X, START_POS_Y + LINE_WIDTH_Y * line);
	line++;
	m_listText.push_back(GameText);
	line++;
	GameText = std::make_shared<Text>(shader, font, "Control: ", TEXT_COLOR::YELLOW, textSize);
	GameText->Set2DPosition(START_POS_X, START_POS_Y + LINE_WIDTH_Y * line);
	line++;
	m_listText.push_back(GameText);

	GameText = std::make_shared<Text>(shader, font, "- Mouse: Move your plane with mouse.", TEXT_COLOR::CYAN, textSize);
	GameText->Set2DPosition(START_POS_X + 20, START_POS_Y + LINE_WIDTH_Y * line);
	line++;
	m_listText.push_back(GameText);

	GameText = std::make_shared<Text>(shader, font, "Left button to shoot!", TEXT_COLOR::CYAN, textSize);
	GameText->Set2DPosition(START_POS_X + 80, START_POS_Y + LINE_WIDTH_Y * line);
	line++;
	m_listText.push_back(GameText);

	GameText = std::make_shared<Text>(shader, font, "- Keyboard: WASD to move. Press Space to shoot.", TEXT_COLOR::BLUE, textSize);
	GameText->Set2DPosition(START_POS_X + 20, START_POS_Y + LINE_WIDTH_Y * line);
	line++;
	m_listText.push_back(GameText);

	GameText = std::make_shared<Text>(shader, font, "- Pause: Press P to pause.", TEXT_COLOR::WHILE, textSize);
	GameText->Set2DPosition(START_POS_X + 20, START_POS_Y + LINE_WIDTH_Y * line);
	line++;
	m_listText.push_back(GameText);
}

void GSInfo::Exit()
{
}

void GSInfo::Pause()
{
}

void GSInfo::Resume()
{
}

void GSInfo::HandleEvents()
{
}

void GSInfo::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSInfo::HandleTouchEvents(int x, int y, int bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSInfo::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listText)
	{
		it->Update(deltaTime);
	}
}

void GSInfo::Draw()
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